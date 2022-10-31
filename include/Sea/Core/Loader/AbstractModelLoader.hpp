#pragma once

#include "Sea/Core/Loader/IModelLoader.hpp"
#include <Sea/Common/File.hpp>

namespace Sea
{
	class AbstractModelLoader : public IModelLoader
	{
	public:
		AbstractModelLoader(File file) : m_file(file) { }
		AbstractModelLoader(std::string filePath) : AbstractModelLoader(File(filePath)) { } ;

		virtual Ref<Model> Load() = 0;
		virtual std::vector<Mold<Mesh>> GetMeshes() = 0;
		virtual std::vector<glm::mat4> GetMatricesMeshes() = 0;

	protected:
		File m_file;
		std::vector<glm::mat4> matricesMeshes;
		std::vector<Mold<Mesh>> meshes;
		std::vector<glm::vec3> translationsMeshes;
		std::vector<glm::quat> rotationsMeshes;
		std::vector<glm::vec3> scalesMeshes;
	};

}