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

	private:
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mold<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Mold<Texture>> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, Texture::Type _type);
		void SetVertexPos(Vertex& vertex, aiMesh* mesh, u32 i);
		void SetVertexNormal(Vertex& vertex, aiMesh* mesh, u32 i);
		void SetVertexTexCoords(Vertex& vertex, aiMesh* mesh, u32 i);

	public:
		u32 FlagsProperties{};
	private:
		const aiScene* m_scene;
		Assimp::Importer m_importer;
		std::string m_directory;
		std::vector<Mold<Texture>> m_texturesLoaded;
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
		return CreateRef<Model>(meshes);
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
		std::vector<Mold<Texture>> textures;

		for (u32 i = 0; i < mesh->mNumVertices; i++)
		{	
			Vertex vertex;
			SetVertexPos(vertex, mesh, i);
			if (mesh->HasNormals()) SetVertexNormal(vertex, mesh, i);

			// texture coordinates
			if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
				SetVertexTexCoords(vertex, mesh, i);
			else
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);

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

		std::vector<Mold<Texture>> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, Texture::Type::Diffuse);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Mold<Texture>> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, Texture::Type::Specular);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		std::vector<Mold<Texture>> ambiantMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, Texture::Type::Ambient);
		textures.insert(textures.end(), ambiantMaps.begin(), ambiantMaps.end());

		std::vector<Mold<Texture>> shininessMaps = LoadMaterialTextures(material, aiTextureType_SHININESS, Texture::Type::Shininess);
		textures.insert(textures.end(), shininessMaps.begin(), shininessMaps.end());

// 		std::vector<Mold<Texture>> normalMaps = LoadMaterialTextures(material, aiTextureType_NORMALS, Texture::Type::Normal);
// 		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

		return Mould<Mesh>(vertices, indices, textures);
	}

	std::vector<Mold<Texture>> AssimpModelLoader::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, Texture::Type _type)
	{
		std::vector<Mold<Texture>> textures;
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
				m_texturesLoaded.push_back(Mould<Texture>(
					File(m_directory + "/" + str.C_Str(), false), _type, i)
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

}