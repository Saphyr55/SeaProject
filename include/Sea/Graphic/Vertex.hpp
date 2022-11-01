#pragma once

#include <glm/glm.hpp>

namespace Sea
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec3 Color;
		glm::vec2 TexUV;
	};

}