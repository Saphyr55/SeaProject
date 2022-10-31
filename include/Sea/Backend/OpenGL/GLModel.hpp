#pragma once

#include <Sea/Core/Loader/ILoader.hpp>
#include <Sea/Graphic/Model.hpp>

namespace Sea::Backend::OpenGL
{

    class Shader;
    class Camera;

    class GLModel : public Model
    {
    public:
        GLModel(Ref<ILoader> loader);
        ~GLModel();

        void Draw(Shader& shader, Camera& camera);

    };
}
