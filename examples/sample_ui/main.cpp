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
#include <Sea/Ui/Container.hpp>

using namespace Sea;

class SampleUI : public Handler<Window&>
{
public:
	void OnInit();
	void Handle(Sea::Window& window);
	void UpdateBox();

public:
	SampleUI(Application& app, Window& window);

private:
	Camera m_camera;
	EventHandler m_event_handler;
	Window& window;
	Application& m_application;
	std::shared_ptr<Container> container;
	std::shared_ptr<Shader> m_default_shader;
	std::unique_ptr<Shape> m_shape;
};

void SampleUI::UpdateBox()
{
	container->Draw();
	// fmt::print("{}: \n", container->GetDepth());
	// for (auto c : container->Childrens()) {
	//	fmt::print("\t{}\n", c->GetDepth());
	// }
}

void SampleUI::OnInit()
{	
	container = Container::From(window, [&](UiProperties& p)
	{
		p.PosX		= Constraint::Center();
		p.PosY		= Constraint::Center();
		p.Width		= Constraint::Pixel(200.0f);
		p.Height	= Constraint::Pixel(200.0f);
		p.Colour	= Colors::Red;
	});
	
	container->Add
	({
		Component::New([&](UiProperties& p)
		{
			p.Height	= Constraint::Pixel(100.0f);
			p.Width		= Constraint::Pixel(100.0f);
			p.PosX		= Constraint::Center();
			p.PosY		= Constraint::Center();
			p.Colour	= Colors::Blue;
			p.Border	= Constraint::Pixel(30.0f);
		}),
		Component::New([&](UiProperties& p)
		{
			p.Height	= Constraint::Pixel(50.0f);
			p.Width		= Constraint::Pixel(50.0f);
			p.PosX		= Constraint::Center();
			p.PosY		= Constraint::Center();
			p.Colour	= Colors::Yellow;
			p.Border	= Constraint::Pixel(25.0f);
		}),
	});

}

void SampleUI::Handle(Window& window)
{
	Renderer& renderer = window.GetRenderer();

	renderer.Clear();
	renderer.ClearColor(Colors::White);

	// auto mp = Mouse::GetMousePosition();
	// fmt::print("Mouse Position x={} y={}\n", mp.x, mp.y);

	UpdateBox();

	window.Viewport();
	m_event_handler.Handle(m_application);
}

SampleUI::SampleUI(Application& app, Window& window) :
	window(window), 
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
	auto o = std::make_shared<SampleUI>(sea, *window);
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

