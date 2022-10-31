#pragma once

#include <utility>
#include <iostream>
#include <filesystem>

#include <mcl/Logger.hpp>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Sea/Common/Color.hpp>

#include <Sea/Core/Game.hpp>
#include <Sea/Core/Input/Input.hpp>
#include <Sea/Core/Mold.hpp>

#include <Sea/Renderer/Camera.hpp>

#include <Sea/Backend/OpenGL/GL.hpp>
#include <Sea/Backend/OpenGL/GLMesh.hpp>
#include <Sea/Backend/OpenGL/GLTexture.hpp>
#include <Sea/Backend/OpenGL/GLVertexArray.hpp>
#include <Sea/Backend/OpenGL/GLVertexBuffer.hpp>
#include <Sea/Backend/OpenGL/GLElementBuffer.hpp>

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
	void Input(f32 dt);
	void DefaultCursor();
	void CameraCursor();
	glm::vec3 DampedString(const glm::vec3 currentPos, const glm::vec3 targetPos, f32 frametime, f32 springStrength);

	MyGame()=default;
	MyGame(const MyGame&) = default;
	MyGame(MyGame&&) = default;
	~MyGame() = default;

private:
	Ref<Camera> camera;

	Ref<Shader> shader;
	Ref<Shader> shaderLight;

	Ref<Mesh> floor;
	Ref<Mesh> light;

	static Vertex vertices[], lightVertices[];
	static u32 indices[], lightIndices[];
	
	f32 initSpeed = .025f;
	f32 speed = initSpeed;
	s32 state = 1;
	f32 ambientWorld = 0.19f;
	u32 specularAmountPow = 16;
};

Vertex MyGame::vertices[] =
{
	Vertex{ glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
	Vertex{ glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },
	Vertex{ glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
	Vertex{ glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f) }
};

u32 MyGame::indices[] =
{
	0, 1, 2,
	0, 2, 3
};

Vertex MyGame::lightVertices[] =
{
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f) },
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f) },
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)  },
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)  },
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f) },
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f) },
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)  },
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)  }
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
	camera = CreateRef<Camera>(GetWindow().GetProperties().Width, GetWindow().GetProperties().Height, glm::vec3(0.0f, 0.5f, 2.0f));

	switch (state)
	{
	case 0:
		DefaultCursor();
		break;
	case 1:
		CameraCursor();
		break;
	default:
		break;
	}

	Ref<Texture> textures[] =
	{
		Mould<Texture>(File("./examples/res/planks.png"), Texture::Type::DIFFUSE, 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Mould<Texture>(File("./examples/res/planksSpec.png"), Texture::Type::SPECULAR, 1, GL_RED, GL_UNSIGNED_BYTE)
	};

	// Default shader
	shader = Mould<Shader>(File("./examples/shaders/shader.vert"), File("./examples/shaders/shader.frag"));
	// Light shader
	shaderLight = Mould<Shader>(File("./examples/shaders/light.vert"), File("./examples/shaders/light.frag"));
	
	// Store mesh data in vectors for the mesh
	std::vector<Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector<u32> ind(indices, indices + sizeof(indices) / sizeof(u32));
	std::vector<Ref<Texture>> texs;
	texs.push_back(textures[0]);
	texs.push_back(textures[1]);

	// Create floor mesh
	floor = Mould<Mesh>(verts, ind, texs);

	// Store mesh data in vectors for the mesh
	std::vector<Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector<u32> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(u32));

	// Create light mesh
	light =	Mould<Mesh>(lightVerts, lightInd, texs);

	auto lightColor = Colors::White.toVec4f();
	auto lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	auto lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	auto floorPos = glm::vec3(0.0f, 0.0f, 0.0f);
	auto floorModel = glm::mat4(1.0f);
	floorModel = glm::translate(floorModel, floorPos);

	shaderLight->Use();
	shaderLight->SetMatrix4fv("model", lightModel);
	shaderLight->SetVec4f("lightColor", lightColor);

	shader->Use();
	shader->SetMatrix4fv("model", floorModel);
	shader->SetVec4f("lightColor", lightColor);
	shader->SetVec3f("lightPos", lightPos);
	shader->Set1Float("ambient", ambientWorld);
	shader->Set1UInt("specAmountPow", specularAmountPow);

}

void MyGame::After()
{	
	shaderLight->Delete();
	shader->Delete();
}

void MyGame::Render()
{
	GetRenderer().ClearColor(Colors::Black);
	GetRenderer().Clear();
	GetWindow().Viewport();

	camera->SetViewProjection(45.0f, 0.1f, 100.0f);
	
 	floor->Draw(*shader, *camera);
 	light->Draw(*shaderLight, *camera);
}

void MyGame::Update(f32 dt)
{	
	Input(dt);
	if (state == 1)
	{
		Mouse::OnMoved([&]() 
		{
			f32 sensitivity = .1f;
			camera->Yaw += Mouse::RelativePosX * sensitivity;
			camera->Pitch += Mouse::RelativePosY * sensitivity;

			if (camera->Pitch > 89.0f) camera->Pitch = 89.0f;
			if (camera->Pitch < -89.0f) camera->Pitch = -89.0f;

			camera->SetOrientation(camera->Yaw, camera->Pitch);
		});
	}


}

void MyGame::Input(f32 dt)
{
	speed *= dt;

	glm::vec3 targetPos = camera->Position;

	if (Input::IsKeyDown(Key::Keys::Z))
	{
		targetPos += speed * camera->Orientation;
	}

	if (Input::IsKeyDown(Key::Keys::S))
	{
		targetPos += speed * -camera->Orientation;
	}

	if (Input::IsKeyDown(Key::Keys::Q))
	{
		targetPos += speed * -glm::normalize(glm::cross(camera->Orientation, camera->Up));
	}

	if (Input::IsKeyDown(Key::Keys::D))
	{
		targetPos += speed * glm::normalize(glm::cross(camera->Orientation, camera->Up));
	}

	if (Input::IsKeyDown(Key::Keys::LSHIFT))
	{
		targetPos += speed * -camera->Up;
	}

	if (Input::IsKeyDown(Key::Keys::SPACE))
	{
		targetPos += speed * camera->Up;
	}

	if (Input::IsKeyDown(Key::Keys::LCTRL))
	{	
		speed = initSpeed * 2;
	}
	else
	{
		speed = initSpeed;
	}

	camera->Position = DampedString(camera->Position, targetPos, dt, 1);

	if (Input::IsKeyPressed(Key::Keys::ESCAPE))
	{
		switch (state)
		{
		case 0:
			state = 1;
			CameraCursor();
			break;
		case 1:
			state = 0;
			DefaultCursor();
			break;
		default:
			break;
		}
	}

}

void MyGame::DefaultCursor()
{
	GetWindow().SetMouseOnMiddlePosistion();
	GetWindow().UngrapMouse();
	Mouse::ShowCursor(true);
	Mouse::SetRelativeMouseMode(false);
}

void MyGame::CameraCursor()
{
	GetWindow().SetMouseOnMiddlePosistion();
	GetWindow().GrapMouse();
	Mouse::ShowCursor(false);
	Mouse::SetRelativeMouseMode(true);
}

glm::vec3 MyGame::DampedString(const glm::vec3 currentPos, const glm::vec3 targetPos, f32 frametime, f32 springStrength)
{
	glm::vec3 displacement = targetPos - currentPos;
	f32 displacementLength = displacement.length();
	if (displacementLength == 0.f)
		return currentPos;
	f32 invDisplacementLength = 1.f / displacementLength;
	const f32 dampConstant = 0.000065f; 
	f32 springMagitude = springStrength * displacementLength + dampConstant * invDisplacementLength;
	f32 scalar = std::min(invDisplacementLength * springMagitude * frametime, 1.f);
	displacement *= scalar;
	return currentPos + displacement;
}