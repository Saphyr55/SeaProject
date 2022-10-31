#pragma once

#include "Sea/Core/Mold.hpp"
#include "Sea/Graphic/Mesh.hpp"

namespace Sea
{

	class Model;

	class IModelLoader
	{
	public:
		virtual std::vector<Mold<Mesh>> GetMeshes() = 0;
		virtual std::vector<glm::mat4> GetMatricesMeshes() = 0;
		virtual Ref<Model> Load() = 0;
	};
}