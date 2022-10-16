#include <Sea/Backend/OpenGL/GLWindow.hpp>
#include <Sea/Backend/OpenGL/GL.hpp>

namespace Sea::Backend
{
    OpenGL::GLWindow::GLWindow(std::string title, int width, int height)
        : GameWindow(title, width, height)
    {
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        gladLoadGLLoader(SDL_GL_GetProcAddress);
        m_handle = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
        SDL_HideWindow(m_handle);
        SDL_GL_CreateContext(m_handle);
        
    }
}


