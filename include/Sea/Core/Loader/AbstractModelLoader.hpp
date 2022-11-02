#pragma once

#include "Sea/Core/Loader/IModelLoader.hpp"
#include "Sea/Common/File.hpp"

namespace Sea
{
	class AbstractModelLoader : public IModelLoader
	{
	public:
		AbstractModelLoader(std::string_view filepath) : m_file(CreateRef<File>(filepath)) { }
		AbstractModelLoader(const AbstractModelLoader&) = default;
		AbstractModelLoader(AbstractModelLoader&&) = default;
		~AbstractModelLoader() = default;

		virtual Ref<Model> Load() = 0;
		std::vector<Mold<Mesh>> GetMeshes() { return meshes; }
		std::vector<glm::mat4> GetMatricesMeshes() { return matricesMeshes; }

	protected:
		Ref<File> m_file;
		std::vector<glm::mat4> matricesMeshes;
		std::vector<Mold<Mesh>> meshes;
		std::vector<glm::vec3> translationsMeshes;
		std::vector<glm::quat> rotationsMeshes;
		std::vector<glm::vec3> scalesMeshes;
	};

}