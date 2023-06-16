#include <glm/ext.hpp>
#include "Sea/Graphics/Drawing/Box.hpp"
#include "Sea/Graphics/Vertex.hpp"
#include "Sea/Graphics/Mesh.hpp"
#include "Sea/Graphics/Rendering/Window.hpp"
#include "Sea/Core/Color.hpp"

namespace Sea	
{


	Box::Box(Window& window, Shader& shader)
		: shader(shader), window(window)
	{
		std::vector<Vertex> vertices
		{
			Vertex{ glm::vec3( 1.0f,  1.0f, -1.0f) },
			Vertex{ glm::vec3( 1.0f, -1.0f, -1.0f) },
			Vertex{ glm::vec3(-1.0f, -1.0f, -1.0f) },
			Vertex{ glm::vec3(-1.0f,  1.0f, -1.0f) },
		};

		std::vector<u32> indices 
		{ 
			0, 2, 1,
			3, 2, 0,
		};

		m_mesh = renderer.CreateMesh(vertices, indices);
	}
	
	void Box::Draw()
	{		
		auto size = window.GetSize();
		auto window_width = size.first;
		auto window_height = size.second;
		auto w = m_width  / window_width;
		auto h = m_height / window_height;

		shader.Use();
		shader.SetMatrix4fv("cameraProjectionView", glm::mat4(
			w, 0, 0, 0,
			0, h, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		));
		
		auto x = m_x / window_width;
		auto y = m_y / window_height;

		auto model = glm::translate(glm::mat4(1), glm::vec3(x, y, 0));

		shader.SetMatrix4fv("model", model);
		m_mesh->Draw(shader);
	}


}


