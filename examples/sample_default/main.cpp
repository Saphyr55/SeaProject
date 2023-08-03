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
#include <Sea/Graphics/Drawing/Rectangle.hpp>
#include <Sea/Graphics/Rendering/WindowFactory.hpp>

using namespace Sea;

void HandleInput(Window& window, Camera& camera, f32 dt);
void DefaultCursor(Window& window);
void CameraCursor(Window& window);
glm::vec3 DampedString(const glm::vec3 currentPos, const glm::vec3 targetPos, f32 frametime, f32 springStrength);

glm::vec3 generiPos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::mat4 generiModel = glm::mat4(1.0f);
glm::mat4 grindstoneModel = glm::mat4(1.0f);
glm::vec3 grindstonePos = glm::vec3(0.0f, 0.0f, 0.0f);
f32 ambientWorld = 0;
f32 initSpeed = .025f;
f32 speed = initSpeed;
s32 state = 1;
f32 sensitivity = .1f;

class Object : public Handler<Window&>
{

public:
	void Handle(Sea::Window& window)
	{
		auto& renderer = window.GetRenderer();
		auto& clock = window.GetClock();
		auto frame_rate = window.GetFrameRate();
		auto title = fmt::format("Sample - {} fps ", frame_rate.GetFPS());

		renderer.ClearColor(Sea::Colors::EerieBlack);
		renderer.Clear();
		window.Viewport();
		window.SetTitle(title);

		// Setup Perspective Camera
		m_camera.SetViewProjection(45.0f, 0.1f, 500.0f);

		m_box->Draw();

		// Draw the environment
		m_ground->Draw(*m_shader, m_camera);
		m_grass->Draw(*m_shader, m_camera);
		m_grindstone->Draw(*m_shader, m_camera, grindstoneModel, grindstonePos);

		// Lightning the scene
		m_light.Draw(*m_shader);
		// Draw a cube representing where the light from
		m_light.DrawMesh(*m_light_shader, m_camera);

		// Handle input camera
		HandleInput(window, m_camera, clock.Delta);

		// Handle mouse camera if we are in relative mode
		if (state == 1)
		{
			Sea::Mouse::OnMoved([&]()
			{
				m_camera.Yaw += Sea::Mouse::RelativePosX * sensitivity;
				m_camera.Pitch += Sea::Mouse::RelativePosY * sensitivity;
				m_camera.Pitch = Sea::Clamp(m_camera.Pitch, -89.0f, 89.0f);
				m_camera.SetOrientation(m_camera.Yaw, m_camera.Pitch);
			});
		}

		m_event_handler.Handle(window);
	}

public:
	Object(Application& app, Window& window, Camera& camera);

private:
	Window& m_window;
	Camera& m_camera;
	Application& m_application;
	EventHandler m_event_handler;
	PointLight m_light;
	Ref<Shader> m_shader;
	Ref<Shader> m_light_shader;
	Ref<Model> m_ground;
	Ref<Model> m_grass;
	Ref<Model> m_grindstone;
	std::unique_ptr<Rectangle> m_box;
};

Object::Object(Application& app, Window& window, Camera& camera) :
	m_window(window), m_application(app), m_camera(camera)
{
	// Setup a point light
	{
		m_light.Position = glm::vec3(0.0f, 10.0f, 0.0f);
		m_light.Quadratic = 0.000007;
		m_light.Linear = 0.0014;
	}

	m_shader = window
		.GetRenderer()
		.CreateShader(
			"src/Sea/Resources/Shaders/default.vert",
			"src/Sea/Resources/Shaders/default.frag"
		);

	m_box = std::make_unique<Rectangle>(m_window, *m_shader);

	// Ground
	Sea::AssimpModelLoader groundModelLoader("assets/md/ground/scene.gltf");
	m_ground = groundModelLoader.Load();

	// Grindstone
	Sea::AssimpModelLoader grindstoneLoader("assets/md/grindstone/scene.gltf");
	m_grindstone = grindstoneLoader.Load();

	// Model grass
	Sea::AssimpModelLoader grassModelLoader("assets/md/grass/scene.gltf");
	m_grass = grassModelLoader.Load();

	// Light shader
	m_light_shader = m_window
		.GetRenderer()
		.CreateShader(
			"src/Sea/Resources/Shaders/light.vert",
			"src/Sea/Resources/Shaders/light.frag"
		);

}

void InitApplication() 
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
		videoMode.Maximazed = true;
	};

	Camera camera
	(
		videoMode.Width,
		videoMode.Height,
		glm::vec3(0.0, 0.0, 0.0)
	);

	// Creating the window from the application with video mode
	auto window = windowFactory.CreateOpenGLWindow(title, videoMode);
	CameraCursor(*window);

	auto o = std::make_shared<Object>(sea, *window, camera);
	window->Attach(o);
	sea.Attach(window);
	sea.Launch();
}

int main(int argc, const char** argv)
{	
	try
	{	
		InitApplication();
	}
	catch (const std::exception& e)
	{
		fmt::print("{}\n", e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void HandleInput(Window& window, Camera& camera, f32 dt)
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

void DefaultCursor(Window& window)
{
	window.SetMouseOnMiddlePosistion();
	window.UngrapMouse();
	Sea::Mouse::ShowCursor(true);
	Sea::Mouse::SetRelativeMouseMode(false);
}

void CameraCursor(Window& window)
{
	window.SetMouseOnMiddlePosistion();
	window.GrapMouse();
	Sea::Mouse::ShowCursor(false);
	Sea::Mouse::SetRelativeMouseMode(true);
}

glm::vec3 DampedString(const glm::vec3 currentPos, const glm::vec3 targetPos, f32 frametime, f32 springStrength)
{
	glm::vec3 displacement = targetPos - currentPos;
	if (displacement.length() == 0.f) return currentPos;
	f32 invDisplacementLength = 1.f / displacement.length();
	const f32 dampConstant = 0.000065f;
	f32 springMagitude = springStrength * displacement.length() + dampConstant * invDisplacementLength;
	f32 scalar = std::min(invDisplacementLength * springMagitude * frametime, 1.f);
	displacement *= scalar;
	return currentPos + displacement;
}