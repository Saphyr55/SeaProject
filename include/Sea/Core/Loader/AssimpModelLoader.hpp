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
		AssimpModelLoader(File file);
		AssimpModelLoader(std::string_view filePath);

		Ref<Model> Load();

	private:
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mold<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Mold<Texture>> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string_view typeName);
		void SetVertexPos(Vertex& vertex, aiMesh* mesh, u32 i);
		void SetVertexNormal(Vertex& vertex, aiMesh* mesh, u32 i);
		void SetVertexTexUV(Vertex& vertex, aiMesh* mesh, u32 i);

	private:
		const aiScene* scene;
		Assimp::Importer importer;
		std::string directory;
		std::vector<Mold<Texture>> textures_loaded;
	};

	Ref<Model> AssimpModelLoader::Load()
	{
		return CreateRef<Model>(meshes);
	}

	AssimpModelLoader::AssimpModelLoader(File file) : AbstractModelLoader(file) 
	{ 
		scene = importer.ReadFile(file.GetPath(), aiProcess_Triangulate | aiProcess_FlipUVs);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			Log::Error() << "Assimp -> " << importer.GetErrorString();
			throw std::exception("AssimpLoaderExpection");
		}
		directory = file.GetPath().substr(0, file.GetPath().find_last_of('/'));

		ProcessNode(scene->mRootNode, scene);
	}
	
	AssimpModelLoader::AssimpModelLoader(std::string_view filePath) : AssimpModelLoader(File(filePath)) { }

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
				SetVertexTexUV(vertex, mesh, i);
			else
				vertex.TexUV = glm::vec2(0.0f, 0.0f);

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

		// process material
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			std::vector<Mold<Texture>> diffuseMaps = LoadMaterialTextures(material,
				aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			std::vector<Mold<Texture>> specularMaps = LoadMaterialTextures(material,
				aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		return Mould<Mesh>(vertices, indices, textures);
	}

	std::vector<Mold<Texture>> AssimpModelLoader::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string_view typeName)
	{
		std::vector<Mold<Texture>> textures;
		for (u32 i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			bool skip = false;

			for (u32 j = 0; j < textures_loaded.size(); j++)
			{	
				auto& current_texture = textures_loaded[j];
				if (fs::path(current_texture->GetFile().GetPath()).compare(fs::path(str.C_Str())))
				{
					textures.push_back(current_texture);
					skip = true;
					break;
				}
			}

			if (!skip) // if texture hasn't been loaded already, load it
			{   
				Texture::Type _type = Texture::Type::Diffuse;
				switch (type)
				{
				case aiTextureType::aiTextureType_SPECULAR:
					_type = Texture::Type::Specular;
					break;
				default:
					break;
				}
				textures_loaded.push_back(Mould<Texture>(
					File(directory + "/" + str.C_Str(), false), _type, i)
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

	void AssimpModelLoader::SetVertexTexUV(Vertex& vertex, aiMesh* mesh, u32 i)
	{
		glm::vec2 vec;
		glm::vec3 vector;
		// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
		// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
		vec.x = mesh->mTextureCoords[0][i].x;
		vec.y = mesh->mTextureCoords[0][i].y;
		vertex.TexUV = vec;
		/*
		vector.x = mesh->mTangents[i].x;
		vector.y = mesh->mTangents[i].y;
		vector.z = mesh->mTangents[i].z;
		vertex.Tangent = vector;
		vector.x = mesh->mBitangents[i].x;
		vector.y = mesh->mBitangents[i].y;
		vector.z = mesh->mBitangents[i].z;
		vertex.Bitangent = vector;
		*/
	}



}