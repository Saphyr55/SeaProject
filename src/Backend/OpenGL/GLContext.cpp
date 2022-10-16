#include <Sea/Backend/OpenGL/GLContext.hpp>
#include <Sea/Backend/OpenGL/Renderer/GLWindow.hpp>

namespace Sea::Backend::OpenGL
{
	
	std::unique_ptr<Window> GLContext::CreateWindow(std::string title, std::uint32_t w, std::uint32_t h)
	{	
		return std::make_unique<GLWindow>(title, w, h);
	}
	
}