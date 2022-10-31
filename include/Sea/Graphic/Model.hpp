#pragma once

#include <Sea/Common/File.hpp>
#include <Sea/Graphic/Shader.hpp>
#include <Sea/Renderer/Camera.hpp>
#include <Sea/Core/Loader/IModelLoader.hpp>

namespace Sea
{
    class Model
    {

    public:
        Model(Ref<IModelLoader> loader);
        Model(std::vector<Mold<Mesh>> meshes, std::vector<glm::mat4> matricesMeshes);
        ~Model() = default;

		void Draw(Shader& shader, Camera& camera,
			glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
			glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
		);

    protected:
        std::vector<Mold<Mesh>> meshes;
        std::vector<glm::mat4> matricesMeshes;
    };
}
