#pragma once

#include <filesystem>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <mcl/Logger.hpp>

#include "Sea/Graphic/Loader/ModelLoader.hpp"
#include "Sea/Graphic/Rendering/Renderer.hpp"

using mcl::Log;
namespace fs = std::filesystem;

namespace Sea
{

	class AssimpModelLoader : public ModelLoader
	{
	public:
		Ref<Model> Load();
		inline void FlipUVs() { FlagsProperties |= aiProcess_FlipUVs; };
		AssimpModelLoader(std::string_view filepath);
		AssimpModelLoader(const AssimpModelLoader&) = default;
		AssimpModelLoader(AssimpModelLoader&&) = default;
		~AssimpModelLoader() = default;

		static Texture::Type AssimpTextureTypeToSeaTextureType(aiTextureType type);
	private:
		void ProcessNode(aiNode* node, const aiScene* scene);
		Ref<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<RTexture>LoadMaterialTextures(aiMaterial* mat, aiTextureType type);
		void SetVertexPos(Vertex& vertex, aiMesh* mesh, u32 i);
		void SetVertexNormal(Vertex& vertex, aiMesh* mesh, u32 i);
		void SetVertexTexCoords(Vertex& vertex, aiMesh* mesh, u32 i);

	public:
		u32 FlagsProperties{};
	private:
		Ref<Renderer> renderer;
		const aiScene* m_scene;
		Assimp::Importer m_importer;
		std::string m_directory;
		std::vector<RTexture> m_texturesLoaded;
	};

}