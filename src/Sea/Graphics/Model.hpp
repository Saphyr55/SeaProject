#pragma once

#include "Sea/Graphics/Shaders/Shader.hpp"
#include "Sea/Graphics/Rendering/Camera.hpp"
#include "Sea/Graphics/Loader/ModelLoader.hpp"

namespace Sea
{
    class Model
    {

    public:
        void Draw(Shader& shader, Camera& camera,
            glm::mat4 model = glm::mat4(1.f),
			glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
			glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
		);

        std::vector<Ref<Texture>> GetTextures(u32 index);
		std::vector<Ref<Texture>> GetTextures();

    public:
		Model() = default;
		Model(Ref<ModelLoader> loader);
		Model(std::vector<Ref<Mesh>> meshes);
		Model(std::vector<Ref<Mesh>> meshes, std::vector<glm::mat4> matrices_meshes);
		~Model() = default;

    protected:
        std::vector<Ref<Mesh>> m_meshes;
        std::vector<glm::mat4> m_matrices_meshes;
    };

    using RModel = Ref<Model>;

}
