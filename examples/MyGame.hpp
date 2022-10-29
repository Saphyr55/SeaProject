#pragma once

#include <iostream>
#include <filesystem>

#include <Sea/Core/Game.hpp>
#include <Sea/Core/Input/Input.hpp>
#include <Sea/Common/Color.hpp>
#include <mcl/Logger.hpp>
#include <Sea/Backend/OpenGL/GL.hpp>
#include <Sea/Backend/OpenGL/GLMesh.hpp>
#include <Sea/Graphic/Shader.hpp>
#include <Sea/Backend/OpenGL/GLVertexBuffer.hpp>
#include <Sea/Backend/OpenGL/GLElementBuffer.hpp>
#include <Sea/Backend/OpenGL/GLVertexArray.hpp>
#include <stb/stb_image.h>
#include <Sea/Backend/OpenGL/GLTexture.hpp>

using namespace Sea::Backend::OpenGL;
using namespace Sea;
using mcl::Log;

class MyGame final : public Game
{

public:
	void Render() override;
	void Update(float dt) override;
	void Before() override;
	void After() override;

	MyGame()=default;
	MyGame(const MyGame&) = default;
	MyGame(MyGame&&) = default;
	~MyGame() = default;

private:
	MeshPtr mesh;
	ShaderPtr shader;
	GLVertexArrayPtr vao;
	GLVertexBufferPtr vbo;
	GLElementBufferPtr ebo;
	GLTexturePtr texture;
};

void MyGame::Before()
{
	f32 vertices[] =
	{
		 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, // top right
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, // bottom left
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f  // top left 
	};

	u32 indices[] = 
	{
		0, 1, 3,   // first triangle
		1, 2, 3,    // second triangle
	};
	
	shader = GetRenderer().CreateShader
	(
		File("./examples/shaders/shader.vert"),
		File("./examples/shaders/shader.frag")
	);

	shader->Use();

	texture = std::make_shared<GLTexture>
	(
			File("./examples/res/image.png"),
			GL_TEXTURE_2D,
			GL_TEXTURE0,
			GL_RGBA,
			GL_UNSIGNED_BYTE
	);

	vao = std::make_shared<GLVertexArray>();
	vao->Bind();
	
	vbo = std::make_shared<GLVertexBuffer>(vertices, sizeof(vertices));
	ebo = std::make_shared<GLElementBuffer>(indices, sizeof(indices));

	vao->LinkVertexBuffer(*vbo, 0, 3, GL_FLOAT, 5 * (sizeof(f32)), (void*)0);
	vao->LinkVertexBuffer(*vbo, 1, 2, GL_FLOAT, 5 * (sizeof(f32)), (void*)(3 * sizeof(f32)));

	vao->Unbind();
	vbo->Unbind();
	ebo->Unbind();
	
	texture->Bind();
	texture->TexUnit(shader, "tex0", 0);

}

void MyGame::After()
{
	vao->Delete();
	vbo->Delete();
	ebo->Delete();
	texture->Delete();
	shader->Delete();
}

void MyGame::Render()
{
	GetWindow().Viewport();
	GetRenderer().ClearColor(Colors::Nothing);
	GetRenderer().Clear();
	shader->Use();
	texture->Bind();
	vao->Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


void MyGame::Update(float dt)
{
	
}