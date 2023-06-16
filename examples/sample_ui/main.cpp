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

std::string title = "Sample";

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
			videoMode.Maximazed = false;
		};

		// Creating the window from the application with video mode
		Sea::Window& window = sea.CreateWindow(title, videoMode);
		Sea::Renderer& renderer = window.GetRenderer();

		// Creating event handler from the window
		Sea::EventHandler eventHandler;

		// Set up Camera
		Sea::Camera camera
		(
			videoMode.Width,
			videoMode.Height,
			glm::vec3(0.0f, 0.0f, 2.0f)
		);

		// Default shader
		Sea::ShaderRef shader = renderer.CreateShader("examples/shaders/default.vert", "examples/shaders/default.frag");
		Sea::Box b(window, *shader);
		b.Position(0, 0);
		b.Size(200, 200);

		// Setup Frame rate and setup Clock for calculate dt through the frame rate
		Sea::Clock clock;
		Sea::FrameRate frameRate;

		while (sea.Active())
		{
			clock.Start(frameRate);
			renderer.ClearColor(Sea::Colors::EerieBlack);
			renderer.Clear();
			window.Viewport();

			// Setup Perspective Camera
			camera.SetViewProjection(45.0f, 0.1f, 500.0f);
			// Draw a cube representing where the light from
			b.Draw();

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

