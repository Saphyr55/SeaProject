#pragma once

#include <glm/glm.hpp>
#include <nlohmann/json.h>

#include "Sea/Common/CommonType.hpp"
#include "Sea/Core/Loader/AbstractLoader.hpp"
#include "Sea/Common/File.hpp"
#include "Sea/Graphic/Vertex.hpp"

using nlohmann::json;

namespace Sea
{
	using vectors3 = std::vector<glm::vec3>;

	class GLTFLoader : public AbstractLoader
	{
	public:
		GLTFLoader(File file);
		GLTFLoader(std::string filePath) : GLTFLoader(File(filePath)) { }
		~GLTFLoader()=default;

		std::vector<Mold<Mesh>> GetMeshes() { return meshes; }
		std::vector<glm::mat4> GetmatricesMeshes() { return matricesMeshes; }


	private:
		void LoadMesh(u32 indiceMesh);
		void TraverseNode(u32 nextNode, glm::mat4 matrix = glm::mat4(1.0f));
		std::vector<u32> GetIndices(json accessor);
		std::vector<Ref<Texture>> GetTextures();
		std::vector<u8> GetData();
		std::vector<f32> GetFloats(json accessor);
		std::vector<Vertex> AssembleVertices(vectors3 positions, vectors3 normals, std::vector<glm::vec2> texUVs);
		std::vector<glm::vec2> GroupFloatsVec2(std::vector<f32> floatVec);
		std::vector<glm::vec3> GroupFloatsVec3(std::vector<f32> floatVec);
		std::vector<glm::vec4> GroupFloatsVec4(std::vector<f32> floatVec);

	private:
		std::vector<std::string> loadedTexName;
		std::vector<Ref<Texture>> loadedTex;
		std::vector<u8> m_data;
		json m_dataJson;
	};
}
