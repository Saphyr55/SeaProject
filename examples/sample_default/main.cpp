#include <iostream>
#include <filesystem>

#include <fmt/printf.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Sea/Core/Color.hpp>
#include <Sea/Core/Utils.hpp>
#include <Sea/Core/Common.hpp>
#include <Sea/Core/File.hpp>
#include <Sea/Core/Application.hpp>
#include <Sea/Core/FrameRate.hpp>
#include <Sea/Math/Matrix4.hpp>
#include <Sea/Input/EventHandler.hpp>
#include <Sea/Input/Input.hpp>
#include <Sea/Graphics/Rendering/Camera.hpp>
#include <Sea/Graphics/Loader/AssimpModelLoader.hpp>
#include <Sea/Graphics/Lights/PointLight.hpp>
#include <Sea/Graphics/Model.hpp>
#include <Sea/Graphics/Lights/SpotLight.hpp>
#include <Sea/Graphics/Lights/DirectionalLight.hpp>
#include <Sea/Graphics/Drawing/Box.hpp>

void HandleInput(Sea::Window& window, Sea::Camera& camera, Sea::f32 dt);
void DefaultCursor(Sea::Window& window);
void CameraCursor(Sea::Window& window);
glm::vec3 DampedString(const glm::vec3 currentPos, const glm::vec3 targetPos, Sea::f32 frametime, Sea::f32 springStrength);

std::string title = "Sample";
glm::vec3 generiPos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::mat4 generiModel = glm::mat4(1.0f);
glm::mat4 grindstoneModel = glm::mat4(1.0f);
glm::vec3 grindstonePos = glm::vec3(0.0f, 0.0f, 0.0f);
Sea::f32 ambientWorld = 0;
Sea::f32 initSpeed = .025f;
Sea::f32 speed = initSpeed;
Sea::s32 state = 1;
Sea::f32 sensitivity = .1f;

int main(int argc, const char** argv)
{	
	try
	{	
		// Init application
		Sea::Application sea;

		// Setup source directory
		Sea::File::FromResources = "../../";

		// Setup video mode
		Sea::VideoMode videoMode;
		{
			videoMode.Resizable = true;
			videoMode.Maximazed = true;
		};
		
		// Creating the window from the application with video mode
		Sea::Window& window = sea.CreateWindow(title, videoMode);
		Sea::Renderer& renderer = window.GetRenderer();
		
		// Creating event handler from the window
		Sea::EventHandler eventHandler;

		// Set up Camera
		Sea::Camera camera (
			videoMode.Width,
			videoMode.Height,
			glm::vec3(0.0f, 0.0f, 2.0f)
		);

		// Ground
		Sea::AssimpModelLoader groundModelLoader("assets/md/ground/scene.gltf");
		Sea::Model ground = *groundModelLoader.Load();

		// Grindstone
		Sea::AssimpModelLoader grindstoneLoader("assets/md/grindstone/scene.gltf");
		Sea::Model grindstone = *grindstoneLoader.Load();

		// Model grass
		Sea::AssimpModelLoader grassModelLoader("assets/md/grass/scene.gltf");
		Sea::Model grass = *grassModelLoader.Load();

		// Default shader
		Sea::ShaderRef shader = renderer.CreateShader("examples/shaders/default.vert", "examples/shaders/default.frag");
		shader->SetFloat("material.shininess0", 8);

		Sea::Box box(window, *shader);

		// Light shader
		Sea::ShaderRef shaderLight = renderer.CreateShader("examples/shaders/light.vert","examples/shaders/light.frag");

		// Setup a point light
		Sea::PointLight light;
		{
			light.Position = glm::vec3(0.0f, 10.0f, 0.0f);
			light.Quadratic = 0.000007;
			light.Linear = 0.0014;
		}

		// Setup relative or not in function of state
		switch (state)
		{
		case 0:
			DefaultCursor(window);
			break;
		case 1:
			CameraCursor(window);
			break;
		default:
			break;
		}

		// Setup Frame rate and setup Clock for calculate dt through the frame rate
		Sea::Clock clock;
		Sea::FrameRate frameRate;
		while (sea.Active())
		{
			clock.Start(frameRate);
			renderer.ClearColor(Sea::Colors::EerieBlack);
			renderer.Clear();
			window.Viewport();
			window.SetTitle(title + " - fps = " + std::to_string(frameRate.GetFPS()));
		
			// Setup Perspective Camera
			camera.SetViewProjection(45.0f, 0.1f, 500.0f);

			box.Draw();

			// Draw the environment
			ground.Draw(*shader, camera);
			grass.Draw(*shader, camera);
			grindstone.Draw(*shader, camera, grindstoneModel, grindstonePos);

			// Lightning the scene
			light.Draw(*shader); 
			// Draw a cube representing where the light from
			light.DrawMesh(*shaderLight, camera); 

			// Handle input camera
			HandleInput(window, camera, clock.Delta);

			// Handle mouse camera if we are in relative mode
			if (state == 1)
			{
				Sea::Mouse::OnMoved([&]() 
				{
					camera.Yaw += Sea::Mouse::RelativePosX * sensitivity;
					camera.Pitch += Sea::Mouse::RelativePosY * sensitivity;
					camera.Pitch = Sea::Clamp(camera.Pitch, -89.0f, 89.0f);
					camera.SetOrientation(camera.Yaw, camera.Pitch);
				});
			}

			eventHandler.HandleEvent(window); 

			// CRITICAL LINE, free the memory
			window.Swap();

			// Calculate the frame rate and dt
			clock.End(frameRate); 
		}

	}
	catch (const std::exception& e)
	{
		fmt::print("{}\n", e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void HandleInput(Sea::Window& window, Sea::Camera& camera, Sea::f32 dt)
{
	glm::vec3 targetPos = camera.Position;

	if (Sea::Input::IsKeyDown(Sea::Keys::Z))
	{
		targetPos += speed * camera.Orientation;
	}

	if (Sea::Input::IsKeyDown(Sea::Keys::S))
	{
		targetPos += speed * -camera.Orientation;
	}

	if (Sea::Input::IsKeyDown(Sea::Keys::Q))
	{
		targetPos += speed * - glm::normalize(glm::cross(camera.Orientation, camera.Up));
	}

	if (Sea::Input::IsKeyDown(Sea::Keys::D))
	{
		targetPos += speed * glm::normalize(glm::cross(camera.Orientation, camera.Up));
	}

	if (Sea::Input::IsKeyDown(Sea::Keys::LSHIFT))
	{
		targetPos += speed * -camera.Up;
	}

	if (Sea::Input::IsKeyDown(Sea::Keys::SPACE))
	{
		targetPos += speed * camera.Up;
	}

	if (Sea::Input::IsKeyDown(Sea::Keys::LCTRL))
	{
		speed = initSpeed * 2;
	}
	else
	{
		speed = initSpeed;
	}

	camera.Position = DampedString(camera.Position, targetPos, dt, 1);

	if (Sea::Input::IsKeyPressed(Sea::Keys::ESCAPE))
	{
		switch (state)
		{
		case 0:
			state = 1;
			CameraCursor(window);
			break;
		case 1:
			state = 0;
			DefaultCursor(window);
			break;
		default:
			break;
		}
	}

}

void DefaultCursor(Sea::Window& window)
{
	window.SetMouseOnMiddlePosistion();
	window.UngrapMouse();
	Sea::Mouse::ShowCursor(true);
	Sea::Mouse::SetRelativeMouseMode(false);
}

void CameraCursor(Sea::Window& window)
{
	window.SetMouseOnMiddlePosistion();
	window.GrapMouse();
	Sea::Mouse::ShowCursor(false);
	Sea::Mouse::SetRelativeMouseMode(true);
}

glm::vec3 DampedString(const glm::vec3 currentPos, const glm::vec3 targetPos, Sea::f32 frametime, Sea::f32 springStrength)
{
	glm::vec3 displacement = targetPos - currentPos;
	if (displacement.length() == 0.f) return currentPos;
	Sea::f32 invDisplacementLength = 1.f / displacement.length();
	const Sea::f32 dampConstant = 0.000065f;
	Sea::f32 springMagitude = springStrength * displacement.length() + dampConstant * invDisplacementLength;
	Sea::f32 scalar = std::min(invDisplacementLength * springMagitude * frametime, 1.f);
	displacement *= scalar;
	return currentPos + displacement;
}