#include "Sea/Graphic/Models/CubeModel.hpp"
#include "Sea/Common/Color.hpp"
#include "Sea/Core/Mold.hpp"

namespace Sea
{	
	CubeModel::CubeModel(Mold<Texture> texture)
	{
		std::vector<Vertex> vertices
		{ 
			 Vertex{ glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f,0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)  , glm::vec2(0.0, 0.0)  },
			 Vertex{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f,0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)  , glm::vec2(1.0, 0.0)  },
			 Vertex{ glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f,0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)	  , glm::vec2(1.0, 1.0)  },
			 Vertex{ glm::vec3(1.0f, -1.0f,  1.0f), glm::vec3(0.0f,0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)   , glm::vec2(0.0, 1.0)  },
			 Vertex{ glm::vec3(-1.0f, 1.0f,  1.0f),  glm::vec3(0.0f, 0.0f, 0.0f),  glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0, 0.0)  },
			 Vertex{ glm::vec3(-1.0f, 1.0f, -1.0f),  glm::vec3(0.0f, 0.0f, 0.0f),  glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0,0.0)  },
			 Vertex{ glm::vec3(1.0f, 1.0f, -1.0f) ,  glm::vec3(0.0f, 0.0f, 0.0f),  glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0,1.0)  },
			 Vertex{ glm::vec3(1.0f, 1.0f,  1.0f) ,  glm::vec3(0.0f, 0.0f, 0.0f),  glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0,1.0)  }
		};

		std::vector<Mold<Texture>> oneTexture{ texture };
 		meshes.push_back(Mould<Mesh>(vertices, indices, oneTexture));
	}

	CubeModel::CubeModel(Color color)
	{
		std::vector<Vertex> vertices
		{
			Vertex{ glm::vec3(-1.0f, -1.0f,  1.0f),glm::vec3(0.0f, 1.0f, 0.0f), color.toVec3f() },
			Vertex{ glm::vec3(-1.0f, -1.0f, -1.0f),glm::vec3(0.0f, 1.0f, 0.0f), color.toVec3f() },
			Vertex{ glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), color.toVec3f() },
			Vertex{ glm::vec3(1.0f, -1.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), color.toVec3f() },
			Vertex{ glm::vec3(-1.0f, 1.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), color.toVec3f() },
			Vertex{ glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), color.toVec3f() },
			Vertex{ glm::vec3(1.0f, 1.0f, -1.0f) , glm::vec3(0.0f, 1.0f, 0.0f), color.toVec3f() },
			Vertex{ glm::vec3(1.0f, 1.0f,  1.0f) , glm::vec3(0.0f, 1.0f, 0.0f), color.toVec3f() }
		};

		meshes.push_back(Mould<Mesh>(vertices, indices));
	}
}
