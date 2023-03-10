#include "Sea/Backend/SDL/Window.hpp"

namespace Sea::Backend 
{

	SDL::Window::Window(std::string_view title, VideoMode& videoMode) : ::Sea::Window(title, videoMode)
	{
		m_flags = SDL_WINDOW_SHOWN;
		if (m_videoMode.Resizable) m_flags |= SDL_WINDOW_RESIZABLE;
		if (m_videoMode.Fullscreen) m_flags |= SDL_WINDOW_FULLSCREEN;
		if (m_videoMode.Maximazed) m_flags |= SDL_WINDOW_MAXIMIZED;
		
#ifdef SeaOpenGL_Context
		m_flags |= SDL_WINDOW_OPENGL;
#endif
		m_handle = SDL_CreateWindow
		(
			m_title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			m_videoMode.Width,
			m_videoMode.Height,
			m_flags
		);

		if (!m_handle) 
			throw std::exception(std::string(
				"Failed to create window" + 
				std::string(SDL_GetError())).c_str());

#ifdef SeaOpenGL_Context
		m_contextPtr = MakeRef<GLContext>(*this); // Create gl context

		gladLoadGLLoader(SDL_GL_GetProcAddress); // Check OpenGL properties

		if (GL_VERSION == NULL) throw std::exception("Enable to init OpenGL");
		Init();
		m_renderer = MakeRef<GLRenderer>();
		m_renderer->Enable();
#endif
		RenderService::Set(m_renderer);
	}

	SDL::Window::~Window()
	{
		SDL_DestroyWindow(m_handle);
	}

	void SDL::Window::Swap()
	{
#ifdef SeaOpenGL_Context
		SDL_GL_SwapWindow(m_handle);
#endif
	}

	bool SDL::Window::IsOpen()
	{
		return m_isOpen;
	}

	void SDL::Window::Hide()
	{
		SDL_HideWindow(m_handle);
	}

	void SDL::Window::Show()
	{
		SDL_ShowWindow(m_handle);
	}

	void SDL::Window::Close()
	{
		m_isOpen = false;
	}

	bool SDL::Window::IsClosed()
	{
		return !m_isOpen;
	}

	void SDL::Window::SetSize(f32 w, f32 h)
	{
		m_videoMode.Width = w;
		m_videoMode.Height = h;
		SDL_SetWindowSize(m_handle, m_videoMode.Width, m_videoMode.Height);
	}

	void SDL::Window::SetResizable(bool resizable)
	{
		m_videoMode.Resizable = resizable;
		SDL_SetWindowResizable(m_handle, (SDL_bool)m_videoMode.Resizable);
	}

	void SDL::Window::SetTitle(std::string_view title)
	{
		m_title = title;
		SDL_SetWindowTitle(m_handle, title.data());
	}

	void SDL::Window::SetMousePostion(f32 x, f32 y)
	{
		SDL_WarpMouseInWindow(nullptr, x, y);
	}

	void SDL::Window::SetMouseOnMiddlePosistion()
	{
		SetMousePostion(m_videoMode.Width / 2, m_videoMode.Height / 2);
	}

	void SDL::Window::GrapMouse()
	{
		SDL_SetWindowMouseGrab(m_handle, SDL_TRUE);
	}

	void SDL::Window::UngrapMouse()
	{
		SDL_SetWindowMouseGrab(m_handle, SDL_FALSE);
	}
	
	void SDL::Window::Update()
	{
		SDL_GetWindowSize(m_handle, (s32*)&m_videoMode.Width, (s32*)&m_videoMode.Height);
	}

	void SDL::Window::Run()
	{
		m_isOpen = true;
	}

	void SDL::Window::UseVSync(bool use)
	{
#ifdef SeaOpenGL_Context
		SDL_GL_SetSwapInterval(use);
#endif
	}


}