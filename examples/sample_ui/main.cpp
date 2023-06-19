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
#include <Sea/Graphics/Drawing/Shape.hpp>
#include <Sea/Graphics/Rendering/WindowFactory.hpp>

using namespace Sea;

class Object : public Handler<Window&>
{
public:
	void OnInit();
	void Handle(Sea::Window& window);
	void UpdateBox();

public:
	Object(Application& app, Window& window);

private:
	Camera m_camera;
	EventHandler m_event_handler;
	Window& m_window;
	Application& m_application;
	std::shared_ptr<Shader> m_default_shader;
	std::unique_ptr<Shape> m_shape;
};

void Object::UpdateBox()
{
	auto wsize = m_window.GetSize();
	auto rsizex = 200;
	auto rsizey = 200;
	m_shape->SetSize(rsizex, rsizey);
	m_shape->SetPosition((wsize.x - rsizex) / 2, (wsize.y- rsizey) / 2); 
	m_shape->Draw();
}

void Object::OnInit()
{	
	m_default_shader = m_window.GetRenderer().CreateShader
	(
		"src/Sea/Resources/Shaders/default.vert",
		"src/Sea/Resources/Shaders/default.frag"
	);
	
	m_shape = std::make_unique<Shape>(
		m_window, Colors::Crimson
	);
}

void Object::Handle(Sea::Window& window)
{
	auto& renderer = window.GetRenderer();

	renderer.Clear();
	renderer.ClearColor(Colors::EerieBlack);

	auto mp = Mouse::GetMousePosition();
	// fmt::print("Mouse Position x={} y={}\n", mp.x, mp.y);

	UpdateBox();

	window.Viewport();
	m_event_handler.Handle(window);
}

Object::Object(Application& app, Window& window) :
	m_window(window), 
	m_application(app),
	m_camera(
		window.GetSize().x, 
		window.GetSize().y, 
		glm::vec3(0.0f, 0.0f, 2.0f)
	)
{
	OnInit();
}

void InitApp()
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
	auto window = windowFactory.CreateOpenGLWindow("Sample", videoMode);
	auto o = std::make_shared<Object>(sea, *window);
	window->Attach(o);
	sea.Attach(window);

	sea.Launch();
}

int main(int argc, const char** argv)
{
	try
	{
		InitApp();
	}
	catch (const std::exception& e)
	{
		fmt::print("{}\n", e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

