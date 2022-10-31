#pragma once

#include "Sea/Core/Mold.hpp"
#include "Sea/Graphic/Mesh.hpp"

namespace Sea
{
	class ILoader
	{
	public:
		virtual std::vector<Mold<Mesh>> GetMeshes() = 0;
		virtual std::vector<glm::mat4> GetmatricesMeshes() = 0;
	};
}