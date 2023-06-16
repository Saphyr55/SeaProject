#include <fmt/printf.h>

#include "Sea/Graphics/Loader/AssimpModelLoader.hpp"
#include "Sea/Graphics/Model.hpp"

namespace Sea
{

	AssimpModelLoader::AssimpModelLoader(std::string_view filepath) : ModelLoader(filepath) { }

	Ref<Model> AssimpModelLoader::Load()
	{	

		fmt::print("Model Load with assimp START : {}.\n", m_file->GetPath());

		m_scene = m_importer.ReadFile(m_file->GetPath(), aiProcess_Triangulate | FlagsProperties );

		if (!m_scene || m_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !m_scene->mRootNode)
		{
			std::string e("AssimpLoaderExpection : " + std::string(m_importer.GetErrorString()));
			throw std::exception(e.c_str());
		}

		m_directory = m_file->GetPath().substr(0, m_file->GetPath().find_last_of('/'));

		ProcessNode(m_scene->mRootNode, m_scene);

		fmt::print("Model Load with assimp END : {}.\n", m_file->GetPath());

		return std::make_shared<Model>(meshes);
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

	Ref<Mesh> AssimpModelLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<u32> indices;
		std::vector<TextureRef> textures;

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

		std::vector<TextureRef> noneMaps2 = LoadMaterialTextures(material, aiTextureType_UNKNOWN);
		textures.insert(textures.end(), noneMaps2.begin(), noneMaps2.end());

		std::vector<TextureRef> noneMaps = LoadMaterialTextures(material, aiTextureType_NONE);
		textures.insert(textures.end(), noneMaps.begin(), noneMaps.end());

		std::vector<TextureRef> diffuseMaps2 = LoadMaterialTextures(material, aiTextureType_BASE_COLOR);
		textures.insert(textures.end(), diffuseMaps2.begin(), diffuseMaps2.end());

		std::vector<TextureRef> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<TextureRef> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		std::vector<TextureRef> ambiantMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT);
		textures.insert(textures.end(), ambiantMaps.begin(), ambiantMaps.end());

		std::vector<TextureRef> shininessMaps = LoadMaterialTextures(material, aiTextureType_SHININESS);
		textures.insert(textures.end(), shininessMaps.begin(), shininessMaps.end());
		
	 	std::vector<TextureRef> normalMaps = LoadMaterialTextures(material, aiTextureType_NORMALS);
	 	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

		return RenderService::Get().CreateMesh(vertices, indices, textures);
	}

	std::vector<TextureRef> AssimpModelLoader::LoadMaterialTextures(aiMaterial* mat, aiTextureType type)
	{
		std::vector<TextureRef> textures;
		for (u32 i = 0; i < mat->GetTextureCount(type); i++)
		{	
			aiString str;
			mat->GetTexture(type, i, &str);
			bool skip = false;

			for (u32 j = 0; j < m_texturesLoaded.size(); j++)
			{	
				auto& current_texture = m_texturesLoaded[j];
				if (fs::path(current_texture->TextureFile().GetPath()).filename() == fs::path(str.C_Str()).filename())
				{	
					textures.push_back(current_texture);
					skip = true;
					break;
				}
			}

			if (!skip) // if texture hasn't been loaded already, load it
			{   
				m_texturesLoaded.push_back(RenderService::Get().CreateTexture(
					File(m_directory + "/" + str.C_Str(), false),
					AssimpTextureTypeToSeaTextureType(type), i)
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

	Texture::Type AssimpModelLoader::AssimpTextureTypeToSeaTextureType(aiTextureType type)
	{
		switch (type)
		{
			case aiTextureType_NONE:                    return Texture::Type::None;
			case aiTextureType_DIFFUSE:                 return Texture::Type::Diffuse;
			case aiTextureType_SPECULAR:                return Texture::Type::Specular;
			case aiTextureType_AMBIENT:                 return Texture::Type::Ambient;
			case aiTextureType_EMISSIVE:				return Texture::Type::Ambient;
			case aiTextureType_HEIGHT:					return Texture::Type::Normal;
			case aiTextureType_NORMALS:					return Texture::Type::Normal;
			case aiTextureType_SHININESS:				return Texture::Type::Shininess;
			case aiTextureType_OPACITY:					return Texture::Type::None;
			case aiTextureType_DISPLACEMENT:			return Texture::Type::None;
			case aiTextureType_LIGHTMAP:				return Texture::Type::None;
			case aiTextureType_REFLECTION:				return Texture::Type::None;
			case aiTextureType_BASE_COLOR:				return Texture::Type::Diffuse;
			case aiTextureType_NORMAL_CAMERA:			return Texture::Type::None;
			case aiTextureType_EMISSION_COLOR:			return Texture::Type::None;
			case aiTextureType_METALNESS:				return Texture::Type::None;
			case aiTextureType_DIFFUSE_ROUGHNESS:		return Texture::Type::None;
			case aiTextureType_AMBIENT_OCCLUSION:		return Texture::Type::None;
			case aiTextureType_SHEEN:					return Texture::Type::None;
			case aiTextureType_CLEARCOAT:				return Texture::Type::None;
			case aiTextureType_TRANSMISSION:			return Texture::Type::None;
			case aiTextureType_UNKNOWN:					return Texture::Type::None;
			case _aiTextureType_Force32Bit:				return Texture::Type::None;
			default:									return Texture::Type::None;
		}
	}

}