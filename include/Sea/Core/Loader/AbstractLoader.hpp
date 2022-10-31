#pragma once

#include "Sea/Core/Loader/ILoader.hpp"
#include <Sea/Common/File.hpp>

namespace Sea
{
	class AbstractLoader : public ILoader
	{
	public:
		AbstractLoader(File file) : m_file(file) { }
		AbstractLoader(std::string filePath) : AbstractLoader(File(filePath)) { } ;

		virtual std::vector<Mold<Mesh>> GetMeshes() = 0;
		virtual std::vector<glm::mat4> GetmatricesMeshes() = 0;

	protected:
		File m_file;
		std::vector<glm::mat4> matricesMeshes;
		std::vector<Mold<Mesh>> meshes;
		std::vector<glm::vec3> translationsMeshes;
		std::vector<glm::quat> rotationsMeshes;
		std::vector<glm::vec3> scalesMeshes;
	};

}