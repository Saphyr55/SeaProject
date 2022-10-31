#pragma once

#include <Sea/Common/File.hpp>
#include <Sea/Graphic/Shader.hpp>
#include <Sea/Renderer/Camera.hpp>
#include <Sea/Core/Loader/ILoader.hpp>

namespace Sea
{
    class Model
    {

    public:
        Model(Ref<ILoader> loader);
        ~Model() = default;

        void Draw(Shader& shader, Camera& camera);

    protected:
        Ref<ILoader> m_loader;
    };
}
