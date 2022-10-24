#pragma once

#include <iostream>
#include <filesystem>

#include <Sea/Core/Game.hpp>
#include <Sea/Core/Input/Input.hpp>
#include <Sea/Common/Color.hpp>
#include <mcl/Logger.hpp>
#include <Sea/Backend/OpenGL/GL.hpp>
#include <Sea/Graphic/Shader.hpp>

using namespace Sea;
using mcl::Log;

class MyGame final : public Game
{

public:
	void Render() override;
	void Update(float dt) override;
	void Before() override;
	void After() override;

private:
	std::shared_ptr<Shader> shader;
	u32 vao, vbo, ebo;
};

void MyGame::Before()
{
	const f32 vertices[] = 
	{
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	const u32 indices[] = 
	{
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	
	shader = GetRenderer().CreateShader(
		File("../../examples/shaders/shader.vert"),
		File("../../examples/shaders/shader.frag")
	);
	shader->Use();

	// Gen
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	// Bind
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Gen ebo and attrib data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);
	
	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void MyGame::After()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	shader->Delete();
}

void MyGame::Render()
{
	GetWindow().Viewport();
	GetRenderer().ClearColor(Colors::Nothing);
	GetRenderer().Clear();
	shader->Use();
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


void MyGame::Update(float dt)
{
	
}