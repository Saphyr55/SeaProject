#include <iostream>

#include <Sea/Common/CommonType.hpp>
#include <Sea/Common/File.hpp>
#include <Sea/Core/Application.hpp>
#include <Sea/Core/VideoMode.hpp>
#include <Sea/Core/Input/EventHandler.hpp>
#include <Sea/Core/FrameRate.hpp>

#include <utility>
#include <iostream>
#include <filesystem>

#include <mcl/Logger.hpp>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Sea/Common/Color.hpp>
#include <Sea/Common/Utils.hpp>
#include <Sea/Core/Input/Input.hpp>

#include <Sea/Graphic/Lights/PointLight.hpp>

#include <Sea/Graphic/Model.hpp>
#include <Sea/Core/Loader/AssimpModelLoader.hpp>
#include <Sea/Graphic/Lights/SpotLight.hpp>
#include <Sea/Graphic/Lights/DirectionalLight.hpp>

void Before(Sea::Window& window);
void Input(Sea::Window& window, Sea::Camera& camera, Sea::f32 dt);
void DefaultCursor(Sea::Window& window);
void CameraCursor(Sea::Window& window);
glm::vec3 DampedString(const glm::vec3 currentPos, const glm::vec3 targetPos, Sea::f32 frametime, Sea::f32 springStrength);

Sea::Mold<Sea::Shader> shader;
Sea::Mold<Sea::Shader> shaderLight;

Sea::ModelRef generi;
glm::vec3 generiPos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::mat4 generiModel = glm::mat4(1.0f);

Sea::Ref<Sea::PointLight> light;

Sea::ModelRef grindstone;
glm::mat4 grindstoneModel = glm::mat4(1.0f);
glm::vec3 grindstonePos = glm::vec3(0.0f, 0.0f, 0.0f);

Sea::f32 ambientWorld = 0;
Sea::f32 initSpeed = .025f;
Sea::f32 speed = initSpeed;
Sea::s32 state = 1;

int main(int argc, const char** argv)
{	
	try
	{	
		// Init application
		Sea::Application sea;

		// Setup source directory
		Sea::File::FromSource = "../../";

		// Setup video mode
		Sea::VideoMode videoMode;
		videoMode.Resizable = true;
		videoMode.Maximazed = true;

		// Window title
		std::string title = "Demo";
		// Creating the window from the application with video mode
		Sea::Window& window = sea.CreateWindow(title, videoMode);
		
		// Creating event handler from the window
		Sea::EventHandler& eventHandler = window.GetEvent();
		
		// Camera
		Sea::Camera camera
		(
			videoMode.Width,
			videoMode.Height,
			glm::vec3(0.0f, 0.0f, 2.0f)
		);

		// Ground
		Sea::AssimpModelLoader groundModelLoader("assets/md/ground/scene.gltf");
		Sea::ModelRef ground = groundModelLoader.Load();

		// Grindstone
		Sea::AssimpModelLoader grindstoneLoader("assets/md/grindstone/scene.gltf");
		grindstone = grindstoneLoader.Load();

		// Model grass
		Sea::AssimpModelLoader grassModelLoader("assets/md/grass/scene.gltf");
		Sea::ModelRef grass = grassModelLoader.Load();
		
		// Setup Frame rate
		Sea::FrameRate frameRate;
		// Setup Clock for calculate dt through the frame rate
		Sea::Clock clock;

		// Default shader
		shader = Sea::Mould<Sea::Shader>(Sea::File("examples/shaders/default.vert"), Sea::File("examples/shaders/default.frag"));
		shader->SetFloat(std::string("material.shininess0"), 8);

		// Light shader
		shaderLight = Sea::Mould<Sea::Shader>(Sea::File("examples/shaders/light.vert"), Sea::File("examples/shaders/light.frag"));

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
		
		// Create a point light
		light = Sea::CreateRef<Sea::PointLight>();
		light->Position = glm::vec3(0.0f, 30.0f, 30.0f);
		light->Quadratic = 0.000007;
		light->Linear = 0.0014;

		while (sea.Active())
		{
			clock.Start(frameRate);
			window.GetRenderer().EnableBlending();
			window.GetRenderer().ClearColor(Sea::Colors::EerieBlack);
			window.GetRenderer().Clear();
			window.Viewport();
			window.SetTitle("Game - " + std::to_string(frameRate.GetFPS()) + " fps");
		
			// Setup Perspective Camera
			camera.SetViewProjection(45.0f, 0.1f, 500.0f);

			ground->Draw(*shader, camera);
			grass->Draw(*shader, camera);
			grindstone->Draw(*shader, camera, grindstoneModel, grindstonePos);

			// Lightning the scene
			light->Draw(*shader); 
			// Draw a cube representing where the light from
			light->DrawMesh(*shaderLight, camera); 

			// Handle input camera
			Input(window, camera, clock.Delta);

			// Handle mouse camera if we are in relative mode
			if (state == 1)
			{
				Sea::Mouse::OnMoved([&]() {
					Sea::f32 sensitivity = .1f;
					camera.Yaw += Sea::Mouse::RelativePosX * sensitivity;
					camera.Pitch += Sea::Mouse::RelativePosY * sensitivity;
					camera.Pitch = Sea::Clamp(camera.Pitch, -89.0f, 89.0f);
					camera.SetOrientation(camera.Yaw, camera.Pitch);
				});
			}

			eventHandler.HandleEvent(); 
			// CRITICAL LINE, free the memory
			window.Swap(); 
			// Calculate the frame rate and dt
			clock.End(frameRate); 
		}

		// remove shaders
		shaderLight->Delete();
		shader->Delete();

	}
	catch (const std::exception &e)
	{
		Log::Error() << e.what();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void Input(Sea::Window& window, Sea::Camera& camera, Sea::f32 dt)
{
	// speed *= dt;

	glm::vec3 targetPos = camera.Position;

	if (Sea::Input::IsKeyDown(Sea::Key::Keys::Z))
	{
		targetPos += speed * camera.Orientation;
	}

	if (Sea::Input::IsKeyDown(Sea::Key::Keys::S))
	{
		targetPos += speed * -camera.Orientation;
	}

	if (Sea::Input::IsKeyDown(Sea::Key::Keys::Q))
	{
		targetPos += speed * - glm::normalize(glm::cross(camera.Orientation, camera.Up));
	}

	if (Sea::Input::IsKeyDown(Sea::Key::Keys::D))
	{
		targetPos += speed * glm::normalize(glm::cross(camera.Orientation, camera.Up));
	}

	if (Sea::Input::IsKeyDown(Sea::Key::Keys::LSHIFT))
	{
		targetPos += speed * -camera.Up;
	}

	if (Sea::Input::IsKeyDown(Sea::Key::Keys::SPACE))
	{
		targetPos += speed * camera.Up;
	}

	if (Sea::Input::IsKeyDown(Sea::Key::Keys::LCTRL))
	{
		speed = initSpeed * 2;
	}
	else
	{
		speed = initSpeed;
	}

	camera.Position = DampedString(camera.Position, targetPos, dt, 1);

	if (Sea::Input::IsKeyPressed(Sea::Key::Keys::ESCAPE))
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