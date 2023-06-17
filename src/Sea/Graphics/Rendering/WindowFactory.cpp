#include "Sea/Graphics/Rendering/WindowFactory.hpp"
#include "Sea/Graphics/Rendering/Window.hpp"
#include "Sea/Graphics/OpenGL/GLWindow.hpp"
#include "Sea/Core/VideoMode.hpp"

namespace Sea
{

    Ref<Window> WindowFactory::CreateOpenGLWindow(std::string_view title, VideoMode& proterties)
    {
        return std::make_shared<GLWindow>(title, proterties);
    }

}
