#include <iostream>
#include <filesystem>

#include <fmt/printf.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Sea/Core/Clock.hpp>
#include <Sea/Core/Color.hpp>
#include <Sea/Core/Utils.hpp>
#include <Sea/Core/Common.hpp>
#include <Sea/Core/File.hpp>
#include <Sea/Core/Application.hpp>
#include <Sea/Core/VideoMode.hpp>
#include <Sea/Core/FrameRate.hpp>

#include <Sea/Input/EventHandler.hpp>
#include <Sea/Input/Input.hpp>

#include <Sea/Graphics/Rendering/Window.hpp>
#include <Sea/Graphics/Rendering/Camera.hpp>
#include <Sea/Graphics/Loader/AssimpModelLoader.hpp>
#include <Sea/Graphics/Lights/PointLight.hpp>
#include <Sea/Graphics/Model.hpp>
#include <Sea/Graphics/Lights/SpotLight.hpp>
#include <Sea/Graphics/Lights/DirectionalLight.hpp>
#include <Sea/Graphics/Drawing/Rectangle.hpp>
#include <Sea/Graphics/Rendering/WindowFactory.hpp>

using namespace Sea;

std::string title = "Sample";

class Object : public Handler<Window&>
{

public:
	void OnInit();
	void Handle(Sea::Window& window);

public:
	Object(Application& app, Window& window);

private:
	Camera m_camera;
	EventHandler m_event_handler;
	Window& m_window;
	Application& m_application;
	std::shared_ptr<Shader> m_default_shader;
	std::unique_ptr<Rectangle> m_rectangle;
};

void Object::OnInit()
{

	m_default_shader = m_window.GetRenderer().CreateShader
	(
		"examples/shaders/default.vert",
		"examples/shaders/default.frag"
	);

	m_rectangle = std::make_unique<Rectangle>(m_window, *m_default_shader);
	m_rectangle->SetSize(50, 50);
	m_rectangle->SetPosition(0, 0);
}

void Object::Handle(Sea::Window& window)
{
	auto& renderer = window.GetRenderer();

	renderer.Clear();
	renderer.ClearColor(Colors::SkyBlue);

	m_rectangle->Draw();
	window.Viewport();
	m_event_handler.Handle(window);
}

Object::Object(Application& app, Window& window) :
	m_window(window), 
	m_application(app),
	m_camera(
		window.GetSize().first, 
		window.GetSize().second, 
		glm::vec3(0.0f, 0.0f, 2.0f)
	)
{
	OnInit();
}

int main(int argc, const char** argv)
{
	try
	{
		// Init application
		Application sea;
		
		// Setup source directory
		File::AssetsFolder = "../../";
		WindowFactory windowFactory;

		// Setup video mode
		VideoMode videoMode;
		{
			videoMode.Resizable = true;
			videoMode.Maximazed = false;
		};

		// Creating the window from the application with video mode
		auto window = windowFactory.CreateOpenGLWindow(title, videoMode);
		auto o = std::make_shared<Object>(sea, *window);
		window->Attach(o);
		sea.Attach(window);
		
		sea.Launch();
	}
	catch (const std::exception& e)
	{
		fmt::print("{}\n", e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

