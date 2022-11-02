#pragma once

#include <glm/glm.hpp>
#include "Sea/Core/Mold.hpp"
#include "Sea/Common/CommonType.hpp"
#include "Sea/Graphic/Mesh.hpp"
#include "Sea/Common/Color.hpp"

namespace Sea
{	
	class Shader;

	class Light
	{
	public:
		Color _Color = Colors::White;
		glm::vec3 Position = glm::vec3();
		glm::vec3 Ambient = glm::vec3(0.2f, 0.2f, 0.2f);
		glm::vec3 Diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		glm::vec3 Specular = glm::vec3(1.0f, 1.0f, 1.0f);

		virtual void Draw(Shader& shader) = 0;
		virtual void DrawMesh(Shader& shader, Camera& camera);

		Light() = default;
		virtual ~Light()= default;

	protected:
		u32 id;
		std::string light;
		glm::mat4 m_meshModel = glm::mat4(1.0f);
		Mold<Mesh> m_mesh;

	private:
		static std::vector<Vertex> lightVertices;
		static std::vector<u32> lightIndices;
	};

	std::vector<Vertex> Light::lightVertices
	{
		Vertex{glm::vec3(-0.05f, -0.05f,  0.05f) },
		Vertex{glm::vec3(-0.05f, -0.05f, -0.05f) },
		Vertex{glm::vec3(0.05f, -0.05f, -0.05f)  },
		Vertex{glm::vec3(0.05f, -0.05f,  0.05f)  },
		Vertex{glm::vec3(-0.05f,  0.05f,  0.05f) },
		Vertex{glm::vec3(-0.05f,  0.05f, -0.05f) },
		Vertex{glm::vec3(0.05f,  0.05f, -0.05f)  },
		Vertex{glm::vec3(0.05f,  0.05f,  0.05f)  }
	};

	std::vector<u32> Light::lightIndices
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
	};

	void Light::DrawMesh(Shader& shader, Camera& camera)
	{
		if (m_mesh)
		{	
			shader.Use();
			shader.SetVec4f("lightColor", _Color.toVec4f());
			m_mesh->Draw(shader, camera, m_meshModel, Position);
		}
		else
		{
			m_mesh = Mould<Mesh>(lightVertices, lightIndices);
			DrawMesh(shader, camera);
		}
	}

	

} // namespace Sea
