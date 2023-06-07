#pragma once

#include "Sea/Core/File.hpp"
#include "Sea/Graphic/Mesh.hpp"

namespace Sea
{
	class Model;

	class ModelLoader
	{
	public:
		ModelLoader(std::string_view filepath) : m_file(MakeRef<File>(filepath)) { }
		ModelLoader(const ModelLoader&) = default;
		ModelLoader(ModelLoader&&) = default;
		~ModelLoader() = default;

		virtual Ref<Model> Load() = 0;
		std::vector<Ref<Mesh>> GetMeshes() { return meshes; }
		std::vector<glm::mat4> GetMatricesMeshes() { return matricesMeshes; }

	protected:
		Ref<File> m_file;
		std::vector<glm::mat4> matricesMeshes;
		std::vector<Ref<Mesh>> meshes;
		std::vector<glm::vec3> translationsMeshes;
		std::vector<glm::quat> rotationsMeshes;
		std::vector<glm::vec3> scalesMeshes;
	};

}