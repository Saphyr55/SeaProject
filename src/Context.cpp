#include <Sea/Context.hpp>
#include <Sea/Backend/OpenGL/GLContext.hpp>

namespace Sea
{

	std::unique_ptr<Context> Context::Of(ContextType contextType)
	{
		switch (contextType)
		{
		case ContextType::OpenGL:
			return std::make_unique<Backend::OpenGL::GLContext>(Backend::OpenGL::GLContext());
		default:
			break;
		}
	}

}
