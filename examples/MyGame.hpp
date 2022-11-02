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

#include <Sea/Graphic/Lights/PointLight.hpp>

#include <Sea/Graphic/Model.hpp>
#include <Sea/Core/Loader/AssimpModelLoader.hpp>
#include <Sea/Graphic/Lights/SpotLight.hpp>
#include <Sea/Graphic/Lights/DirectionalLight.hpp>

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

	Ref<Model> generi;
	glm::vec3 generiPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 generiModel = glm::mat4(1.0f);

	Ref<PointLight> light;

	Ref<Model> grindstone;
	glm::mat4 grindstoneModel = glm::mat4(1.0f);
	glm::vec3 grindstonePos = glm::vec3(0.0f, 5.0f, 0.0f);

	f32 ambientWorld = 1.9f; 
	f32 initSpeed = .025f;
	f32 speed = initSpeed;
	s32 state = 1;
};



void MyGame::Before()
{
	// Default shader
	shader = Mould<Shader>(File("./examples/shaders/shader.vert"), File("./examples/shaders/shader.frag"));
	shader->SetFloat(std::string("material.shininess0"), 8);

	// Light shader
	shaderLight = Mould<Shader>(File("./examples/shaders/light.vert"), File("./examples/shaders/light.frag"));
	// Camera
	camera = CreateRef<Camera>(GetWindow().GetProperties().Width, GetWindow().GetProperties().Height, glm::vec3(0.0f, 0.0f, 2.0f));
		
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
	AssimpModelLoader grindstoneLoader("examples/res/md/grindstone/scene.gltf");
	grindstone = grindstoneLoader.Load();

	light = CreateRef<PointLight>();
	light->Position= glm::vec3(0.0f, 30.0f, 30.0f);
	light->Quadratic = 0.000007;
	light->Linear = 0.0014;
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

	grindstone->Draw(*shader, *camera, grindstoneModel, grindstonePos);

	light->Draw(*shader);
	light->DrawMesh(*shaderLight, *camera);

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
