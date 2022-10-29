#pragma once

#include <iostream>
#include <filesystem>

#include <mcl/Logger.hpp>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Sea/Core/Game.hpp>
#include <Sea/Core/Input/Input.hpp>
#include <Sea/Common/Color.hpp>
#include <Sea/Backend/OpenGL/GL.hpp>
#include <Sea/Backend/OpenGL/GLMesh.hpp>
#include <Sea/Graphic/Shader.hpp>
#include <Sea/Backend/OpenGL/GLVertexBuffer.hpp>
#include <Sea/Backend/OpenGL/GLElementBuffer.hpp>
#include <Sea/Backend/OpenGL/GLVertexArray.hpp>
#include <Sea/Backend/OpenGL/GLTexture.hpp>
#include <Sea/Backend/OpenGL/GLCamera.hpp>

using namespace Sea::Backend::OpenGL;
using namespace Sea;
using mcl::Log;

class MyGame final : public Game
{

public:
	void Render() override;
	void Update(f32 dt) override;
	void Before() override;
	void After() override;

	MyGame()=default;
	MyGame(const MyGame&) = default;
	MyGame(MyGame&&) = default;
	~MyGame() = default;

private:
	ShaderPtr shader;
	GLVertexArrayPtr vao;
	GLVertexBufferPtr vbo;
	GLElementBufferPtr ebo;

	ShaderPtr shaderLight;
	GLVertexArrayPtr vaoLightCube;
	GLVertexBufferPtr vboLightCube;
	GLElementBufferPtr eboLightCube;

	GLTexturePtr texture;
	GLCameraPtr camera;

	static f32 vertices[], lightVertices[];
	static u32 indices[], lightIndices[];

	f32 speed = .01f;
	s32 state = 0;
};

f32 MyGame::vertices[] =
{
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
};

u32 MyGame::indices[] =
{
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
};

f32  MyGame::lightVertices[] =
{
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

u32 MyGame::lightIndices[] =
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

void MyGame::Before()
{
	camera = std::make_shared<GLCamera>
	(	
		GetWindow().GetProperties().Width,
		GetWindow().GetProperties().Height,
		glm::vec3(0.0f, .5f, 2.0f)
	);

	shader = GetRenderer().CreateShader
	(
		File("./examples/shaders/shader.vert"),
		File("./examples/shaders/shader.frag")
	);

	texture = std::make_shared<GLTexture>
	(
		File("./examples/res/brick.png"),
		GL_TEXTURE_2D,
		GL_TEXTURE0,
		GL_RGBA,
		GL_UNSIGNED_BYTE
	);

	vao = std::make_shared<GLVertexArray>();
	vao->Bind();
	
	vbo = std::make_shared<GLVertexBuffer>(vertices, sizeof(vertices));
	ebo = std::make_shared<GLElementBuffer>(indices, sizeof(indices));

	vao->LinkVertexBuffer(*vbo, 0, 3, GL_FLOAT, 11 * (sizeof(f32)), (void*)0);
	vao->LinkVertexBuffer(*vbo, 1, 3, GL_FLOAT, 11 * (sizeof(f32)), (void*)(3 * sizeof(f32)));
	vao->LinkVertexBuffer(*vbo, 2, 2, GL_FLOAT, 11 * (sizeof(f32)), (void*)(6 * sizeof(f32)));
	vao->LinkVertexBuffer(*vbo, 3, 3, GL_FLOAT, 11 * (sizeof(f32)), (void*)(8 * sizeof(f32)));

	vao->Unbind();
	vbo->Unbind();
	ebo->Unbind();
	
	texture->Bind();
	shader->Use();
	shader->Set1Int("tex0", 0);

	shaderLight = GetRenderer().CreateShader
	(
		File("./examples/shaders/light.vert"),
		File("./examples/shaders/light.frag")
	);

	vaoLightCube = std::make_shared<GLVertexArray>();
	vaoLightCube->Bind();

	vboLightCube = std::make_shared<GLVertexBuffer>(lightVertices, sizeof(lightVertices));
	eboLightCube = std::make_shared<GLElementBuffer>(lightIndices, sizeof(lightIndices));

	vaoLightCube->LinkVertexBuffer(*vboLightCube, 0, 3, GL_FLOAT, 3 * sizeof(f32), (void*)0);

	vaoLightCube->Unbind();
	vboLightCube->Unbind();
	eboLightCube->Unbind();

	shaderLight->Use();
	auto lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	auto lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	auto lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);
	shaderLight->SetMatrix4fv("model", lightModel);
	shaderLight->SetVec4f("lightColor", lightColor);

	shader->Use();
	auto pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	auto pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);
	shader->SetMatrix4fv("model", pyramidModel);
	shader->SetVec4f("lightColor", lightColor);
	shader->SetVec3f("lightPos", lightPos);

}

void MyGame::After()
{
	vao->Delete();
	vbo->Delete();
	ebo->Delete();
	
	vaoLightCube->Delete();
	vboLightCube->Delete();
	eboLightCube->Delete();
	
	texture->Delete();

	shaderLight->Delete();
	shader->Delete();
}

void MyGame::Render()
{	
	GetRenderer().ClearColor(Colors::Nothing);
	GetRenderer().Clear();
	GetWindow().Viewport();

	camera->SetViewProjection(45.f, .1f, 100.f);

	shader->Use();
	shader->SetVec3f("cameraPos", camera->Position);
	shader->SetMatrix4fv("cameraProjectionView", camera->ProjectionView);
	texture->Bind();
	vao->Bind();
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(s32), GL_UNSIGNED_INT, 0);

	shaderLight->Use();
	shaderLight->SetMatrix4fv("cameraProjectionView", camera->ProjectionView);
	vaoLightCube->Bind();
	glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(s32), GL_UNSIGNED_INT, 0);
}


void MyGame::Update(f32 dt)
{
	speed = 0.025f * dt;

	if (Input::IsKeyDown(Key::Keys::Z))
	{
		camera->Position += speed * camera->Orientation;
	}

	if (Input::IsKeyDown(Key::Keys::S))
	{
		camera->Position += speed * -camera->Orientation;
	}

	if (Input::IsKeyDown(Key::Keys::Q))
	{
		camera->Position += speed * -glm::normalize(glm::cross(camera->Orientation, camera->Up));
	}

	if (Input::IsKeyDown(Key::Keys::D))
	{
		camera->Position += speed * glm::normalize(glm::cross(camera->Orientation, camera->Up));
	}

	if (Input::IsKeyDown(Key::Keys::LSHIFT))
	{
		camera->Position += speed * -camera->Up;
	}

	if (Input::IsKeyDown(Key::Keys::SPACE))
	{
		camera->Position += speed * camera->Up;
	}

	if (Input::IsKeyPressed(Key::Keys::ESCAPE))
	{
		switch (state)
		{
		case 0:
			state = 1;
			GetWindow().GrapMouse();
			SDL_ShowCursor(SDL_DISABLE);
			break;
		case 1:
			state = 0;
			GetWindow().UngrapMouse();
			SDL_ShowCursor(SDL_ENABLE);
			break;
		default:
			break;
		}
	}

	if (state == 1 && Mouse::IsMouseMoved())
	{	
		f32 sensitivity = 0.1f;
		camera->Yaw += Mouse::RelativePosX * sensitivity;
		camera->Pitch += Mouse::RelativePosY * sensitivity;

		if (camera->Pitch > 89.0f)
			camera->Pitch = 89.0f;
		if (camera->Pitch < -89.0f)
			camera->Pitch = -89.0f;

		glm::vec3 new_orientation;
		new_orientation.x = cos(glm::radians(camera->Yaw)) * cos(glm::radians(camera->Pitch));
		new_orientation.y = sin(glm::radians(-camera->Pitch));
		new_orientation.z = sin(glm::radians(camera->Yaw)) * cos(glm::radians(camera->Pitch));
		camera->Orientation = glm::normalize(new_orientation);

		GetWindow().WrapMouse(GetWindow().GetProperties().Width / 2, GetWindow().GetProperties().Height / 2);
	}

}