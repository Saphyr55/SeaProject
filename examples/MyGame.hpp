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
#include <Sea/Core/Loader/GLTFLoader.hpp>

#include <Sea/Graphic/Model.hpp>
#include <Sea/Core/Loader/AssimpModelLoader.hpp>
#include <Sea/Graphic/Models/CubeModel.hpp>

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
	static Vertex vertices[], lightVertices[];
	static u32 indices[], lightIndices[];

	Ref<Camera> camera;

	Ref<Shader> shader;
	Ref<Shader> shaderLight;

	Ref<Model> lantern;
	glm::vec3 lanterPos = glm::vec3(0.0f, -1.0f, 0.0f);
	glm::mat4 lanternModel = glm::mat4(1.0f);

	Ref<CubeModel> cube;
	glm::vec3 cubePos = glm::vec3(-1.0f, 1.0f, 0.0f);
	glm::mat4 cubeModel = glm::mat4(1.0f);

	Ref<Mesh> light;
	glm::vec3 lightPos = glm::vec3(1.0f, 1.0f, 0.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);

	Ref<IModelLoader> modelLoader;
	Ref<Model> grindstone;
	glm::mat4 grindstoneModel = glm::mat4(1.0f);
	glm::vec3 grindstonePos = glm::vec3(0.0f, 0.0f, 0.0f);

	f32 initSpeed = .025f;
	f32 speed = initSpeed;
	s32 state = 1;
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

	// Grindstone
	
	grindstone = AssimpModelLoader("examples/res/md/grindstone/scene.gltf").Load();
	// Cube
	// cube = CreateRef<CubeModel>(Mould<Texture>(File("examples/res/container.png"), Texture::Type::Diffuse, 0));
	// cube = CreateRef<CubeModel>(Colors::Strawberry);
	// Lantern
	// lantern = AssimpModelLoader("examples/res/md/lantern/Lantern.gltf").Load();

	// Default shader
	shader = Mould<Shader>(File("./examples/shaders/shader.vert"), File("./examples/shaders/shader.frag"));
	// Light shader
	shaderLight = Mould<Shader>(File("./examples/shaders/light.vert"), File("./examples/shaders/light.frag"));
	
	// Store mesh data in vectors for the mesh
	std::vector<Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector<u32> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(u32));
	
	// Create light mesh
	light =	Mould<Mesh>(lightVerts, lightInd, grindstone->GetTextures());
	glm::vec4 lightColor = Colors::White.toVec4f();

	shader->Use();
	shader->SetFloat("material.shininess", 8.0f);
	shader->SetVec3f("light.ambient", 0.2f, 0.2f, 0.2f);
	shader->SetVec3f("light.diffuse", 0.5f, 0.5f, 0.5f); // darken diffuse light a bit
	shader->SetVec3f("light.specular", 1.0f, 1.0f, 1.0f);
	shader->SetVec3f("light.direction", 0.0f, 1.0f, 0.0f);
}

void MyGame::After()
{	
 	shaderLight->Delete();
	shader->Delete();
}

void MyGame::Render()
{
	GetRenderer().ClearColor(Colors::EerieBlack);
	GetRenderer().Clear();
	GetWindow().Viewport();

	camera->SetViewProjection(45.0f, 0.1f, 100.0f);

	shaderLight->Use();
	shaderLight->SetVec4f("lightColor", Colors::White.toVec4f());
	shaderLight->SetVec3f("lightPos", lightPos);

	shader->Use();
	shader->SetVec4f("lightColor", Colors::White.toVec4f());
	shader->SetVec3f("lightPos", lightPos);

	// cube->Draw(*shader, *camera, cubeModel, cubePos);
	grindstone->Draw(*shader, *camera, grindstoneModel, grindstonePos);
	// lantern->Draw(*shader, *camera, lanternModel, lanterPos);
	light->Draw(*shaderLight, *camera, lightModel, lightPos);


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
	// lightPos.x -= .001f * dt;
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
