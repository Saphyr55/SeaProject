#include <glm/ext.hpp>
#include <fmt/core.h>

#include "Sea/Graphics/Drawing/Shape.hpp"
#include "Sea/Graphics/Vertex.hpp"
#include "Sea/Graphics/Mesh.hpp"
#include "Sea/Graphics/Rendering/Window.hpp"

namespace Sea	
{


	Shape::Shape(Window& parent, Color color)
		: parent(parent), color(color)
	{

		std::vector<Vertex> vertices
		{
			Vertex{ glm::vec3( 1.0f,  1.0f, -0.85f), glm::vec3(1.0f), color.ToVec3f() },
			Vertex{ glm::vec3( 1.0f, -1.0f, -0.85f), glm::vec3(1.0f), color.ToVec3f() },
			Vertex{ glm::vec3(-1.0f, -1.0f, -0.85f), glm::vec3(1.0f), color.ToVec3f() },
			Vertex{ glm::vec3(-1.0f,  1.0f, -0.85f), glm::vec3(1.0f), color.ToVec3f() },
		};

		std::vector<u32> indices 
		{ 
			0, 2, 1,
			3, 2, 0,
		};

		m_mesh = renderer.CreateMesh(vertices, indices);
	}
	
	void Shape::Draw()
	{		
		auto mp = Mouse::GetMousePosition();
		auto shader = renderer.ShapeShader();
		auto relative_size = parent.GetSize();
		auto pos = glm::vec3(m_x + (m_width / 2), m_y + (m_height / 2), 1);
		auto scale = glm::vec3((m_width / 2), (m_height / 2), 1);
		auto orho = glm::ortho(0.0f, relative_size.x, relative_size.y, 0.0f, -1.0f, 1.0f);
		auto model = glm::mat4(1);

		model = glm::translate(model, pos);
		model = glm::scale(model, scale);

		shader->Use();
		shader->SetVec2f("shape.size", m_width, m_height);
		shader->SetVec2f("shape.origin", pos.x, pos.y);
		shader->SetMatrix4fv("model", model);
		shader->SetMatrix4fv("projectionView", orho);
		m_mesh->Draw(*shader);
	}


}


