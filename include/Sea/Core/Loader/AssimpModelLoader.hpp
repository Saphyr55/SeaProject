#pragma once

#include <filesystem>

#include "Sea/Core/Loader/AbstractModelLoader.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <mcl/Logger.hpp>

using mcl::Log;
namespace fs = std::filesystem;

namespace Sea
{

	class AssimpModelLoader : public AbstractModelLoader
	{
	public:
		Ref<Model> Load();
		inline void FlipUVs() { FlagsProperties |= aiProcess_FlipUVs; };
		AssimpModelLoader(std::string_view filepath);
		AssimpModelLoader(const AssimpModelLoader&) = default;
		AssimpModelLoader(AssimpModelLoader&&) = default;
		~AssimpModelLoader() = default;

		static Texture2D::Type AssimpTextureTypeToSeaTextureType(aiTextureType type);
	private:
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mold<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Mold<Texture2D>> LoadMaterialTextures(aiMaterial* mat, aiTextureType type);
		void SetVertexPos(Vertex& vertex, aiMesh* mesh, u32 i);
		void SetVertexNormal(Vertex& vertex, aiMesh* mesh, u32 i);
		void SetVertexTexCoords(Vertex& vertex, aiMesh* mesh, u32 i);

	public:
		u32 FlagsProperties{};
	private:
		const aiScene* m_scene;
		Assimp::Importer m_importer;
		std::string m_directory;
		std::vector<Mold<Texture2D>> m_texturesLoaded;
	};

	AssimpModelLoader::AssimpModelLoader(std::string_view filepath) : AbstractModelLoader(filepath) { }

	Ref<Model> AssimpModelLoader::Load()
	{	
		Log::Info() << "Model Load with assimp START :  " << m_file->GetPath();
		m_scene = m_importer.ReadFile(m_file->GetPath(), aiProcess_Triangulate | FlagsProperties );
		if (!m_scene || m_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !m_scene->mRootNode)
		{
			std::string e("AssimpLoaderExpection : " + std::string(m_importer.GetErrorString()));
			throw std::exception(e.c_str());
		}
		m_directory = m_file->GetPath().substr(0, m_file->GetPath().find_last_of('/'));

		ProcessNode(m_scene->mRootNode, m_scene);
		Log::Info() << "Model Load with assimp END : " << m_file->GetPath();
		return MakeRef<Model>(meshes);
	}

	void AssimpModelLoader::ProcessNode(aiNode* node, const aiScene* scene)
	{
		// process all the node's meshes (if any)
		for (u32 i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(ProcessMesh(mesh, scene));
		}
		// then do the same for each of its children
		for (u32 i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	Mold<Mesh> AssimpModelLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<u32> indices;
		std::vector<Mold<Texture2D>> textures;

		for (u32 i = 0; i < mesh->mNumVertices; i++)
		{	
			Vertex vertex;
			SetVertexPos(vertex, mesh, i);
			if (mesh->HasNormals()) SetVertexNormal(vertex, mesh, i);

			// texture coordinates 
			// does the mesh contain texture coordinates?
			if (mesh->mTextureCoords[0]) SetVertexTexCoords(vertex, mesh, i);
			else vertex.TexCoords = glm::vec2(0.0f, 0.0f);

			vertices.push_back(vertex);
		}

		// process indices
		// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
		for (u32 i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			// retrieve all indices of the face and store them in the indices vector
			for (u32 j = 0; j < face.mNumIndices; j++) indices.push_back(face.mIndices[j]);
		}

		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<Mold<Texture2D>> noneMaps2 = LoadMaterialTextures(material, aiTextureType_UNKNOWN);
		textures.insert(textures.end(), noneMaps2.begin(), noneMaps2.end());

		std::vector<Mold<Texture2D>> noneMaps = LoadMaterialTextures(material, aiTextureType_NONE);
		textures.insert(textures.end(), noneMaps.begin(), noneMaps.end());

		std::vector<Mold<Texture2D>> diffuseMaps2 = LoadMaterialTextures(material, aiTextureType_BASE_COLOR);
		textures.insert(textures.end(), diffuseMaps2.begin(), diffuseMaps2.end());

		std::vector<Mold<Texture2D>> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Mold<Texture2D>> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		std::vector<Mold<Texture2D>> ambiantMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT);
		textures.insert(textures.end(), ambiantMaps.begin(), ambiantMaps.end());

		std::vector<Mold<Texture2D>> shininessMaps = LoadMaterialTextures(material, aiTextureType_SHININESS);
		textures.insert(textures.end(), shininessMaps.begin(), shininessMaps.end());
		
// 		std::vector<Mold<Texture>> normalMaps = LoadMaterialTextures(material, aiTextureType_NORMALS);
// 		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

		return Mould<Mesh>(vertices, indices, textures);
	}

	std::vector<Mold<Texture2D>> AssimpModelLoader::LoadMaterialTextures(aiMaterial* mat, aiTextureType type)
	{
		std::vector<Mold<Texture2D>> textures;
		for (u32 i = 0; i < mat->GetTextureCount(type); i++)
		{	
			aiString str;
			mat->GetTexture(type, i, &str);
			bool skip = false;

			for (u32 j = 0; j < m_texturesLoaded.size(); j++)
			{	
				auto& current_texture = m_texturesLoaded[j];
				if (fs::path(current_texture->GetFile().GetPath()).filename() == fs::path(str.C_Str()).filename())
				{	
					textures.push_back(current_texture);
					skip = true;
					break;
				}
			}

			if (!skip) // if texture hasn't been loaded already, load it
			{   
				m_texturesLoaded.push_back(Mould<Texture2D>(
					File(m_directory + "/" + str.C_Str(), false), AssimpTextureTypeToSeaTextureType(type), i)
				); // add to loaded textures
			}
		}
		return textures;
	}

	void AssimpModelLoader::SetVertexPos(Vertex& vertex, aiMesh* mesh, u32 i)
	{
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;
	}

	void AssimpModelLoader::SetVertexNormal(Vertex& vertex, aiMesh* mesh, u32 i)
	{	
		glm::vec3 vector;
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;
	}

	void AssimpModelLoader::SetVertexTexCoords(Vertex& vertex, aiMesh* mesh, u32 i)
	{
		glm::vec2 vecTex;
		glm::vec3 vector;
		// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
		// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
		vecTex.x = mesh->mTextureCoords[0][i].x;
		vecTex.y = mesh->mTextureCoords[0][i].y;
		vertex.TexCoords = vecTex;
		
// 		vector.x = mesh->mTangents[i].x;
// 		vector.y = mesh->mTangents[i].y;
// 		vector.z = mesh->mTangents[i].z;
		// vertex.Tangent = vector;
// 		vector.x = mesh->mBitangents[i].x;
// 		vector.y = mesh->mBitangents[i].y;
// 		vector.z = mesh->mBitangents[i].z;
		// vertex.Bitangent = vector;
		
	}

	Texture2D::Type AssimpModelLoader::AssimpTextureTypeToSeaTextureType(aiTextureType type)
	{
		switch (type)
		{
		case aiTextureType_NONE: return Texture2D::Type::None;
		case aiTextureType_DIFFUSE: return Texture2D::Type::Diffuse;
		case aiTextureType_SPECULAR: return Texture2D::Type::Specular;
		case aiTextureType_AMBIENT: return Texture2D::Type::Ambient;
		case aiTextureType_EMISSIVE: return Texture2D::Type::Ambient;
		case aiTextureType_HEIGHT: return Texture2D::Type::Normal;
		case aiTextureType_NORMALS: return Texture2D::Type::Normal;
		case aiTextureType_SHININESS: return Texture2D::Type::Shininess;
		case aiTextureType_OPACITY: return Texture2D::Type::None;
		case aiTextureType_DISPLACEMENT: return Texture2D::Type::None;
		case aiTextureType_LIGHTMAP: return Texture2D::Type::None;
		case aiTextureType_REFLECTION: return Texture2D::Type::None;
		case aiTextureType_BASE_COLOR: return Texture2D::Type::Diffuse;
		case aiTextureType_NORMAL_CAMERA: return Texture2D::Type::None;
		case aiTextureType_EMISSION_COLOR: return Texture2D::Type::None;
		case aiTextureType_METALNESS: return Texture2D::Type::None;
		case aiTextureType_DIFFUSE_ROUGHNESS: return Texture2D::Type::None;
		case aiTextureType_AMBIENT_OCCLUSION: return Texture2D::Type::None;
		case aiTextureType_SHEEN: return Texture2D::Type::None;
		case aiTextureType_CLEARCOAT: return Texture2D::Type::None;
		case aiTextureType_TRANSMISSION: return Texture2D::Type::None;
		case aiTextureType_UNKNOWN: return Texture2D::Type::None;
		case _aiTextureType_Force32Bit: return Texture2D::Type::None;
		default: return Texture2D::Type::None;
		}
	}

}