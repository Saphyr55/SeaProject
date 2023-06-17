#include <glm/ext.hpp>
#include "Sea/Graphics/Drawing/Rectangle.hpp"
#include "Sea/Graphics/Vertex.hpp"
#include "Sea/Graphics/Mesh.hpp"
#include "Sea/Graphics/Rendering/Window.hpp"

namespace Sea	
{


	Rectangle::Rectangle(Window& window, Shader& shader, Color color)
		: shader(shader), window(window), color(color)
	{

		auto size = window.GetSize();
		auto w = size.first;
		auto h = size.second;

		std::vector<Vertex> vertices
		{
			Vertex{ glm::vec3( 1.0f,  1.0f, -0.85f), color.toVec3f() },
			Vertex{ glm::vec3( 1.0f, -1.0f, -0.85f), color.toVec3f() },
			Vertex{ glm::vec3(-1.0f, -1.0f, -0.85f), color.toVec3f() },
			Vertex{ glm::vec3(-1.0f,  1.0f, -0.85f), color.toVec3f() },
		};

		std::vector<u32> indices 
		{ 
			0, 2, 1,
			3, 2, 0,
		};

		m_mesh = renderer.CreateMesh(vertices, indices);
	}
	
	void Rectangle::Draw()
	{		
		auto size = window.GetSize();
		auto window_width = size.first;
		auto window_height = size.second;

		auto orho = glm::ortho(0.0f, window_width, window_height, 0.0f, -1.0f, 1.0f);
		auto model = glm::mat4(1);

		model = glm::translate(model, glm::vec3(m_x + m_width, m_y + m_height, 1));
		model = glm::scale(model, glm::vec3(m_width, m_height, 1));

		shader.Use();
		shader.SetMatrix4fv("model", model);
		shader.SetMatrix4fv("cameraProjectionView", orho);
		m_mesh->Draw(shader);
	}

	void Rectangle::SetPosition(f32 x, f32 y)
	{
		SetPosX(x);
		SetPosY(y);
	}

	void Rectangle::SetSize(f32 width, f32 height)
	{
		SetWidth(width);
		SetHeight(height);
	}

}


