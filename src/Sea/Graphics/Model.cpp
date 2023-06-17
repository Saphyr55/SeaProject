#include <Sea/Graphics/Model.hpp>

namespace Sea
{

	Model::Model(std::vector<Ref<Mesh>> meshes, std::vector<glm::mat4> matricesMeshes) :
        m_matrices_meshes(matricesMeshes), m_meshes(meshes)
	{
	}

	Model::Model(std::vector<Ref<Mesh>> meshes) :
        m_meshes(meshes)
	{
	}

	Model::Model(Ref<ModelLoader> loader) : m_matrices_meshes(loader->GetMatricesMeshes()), m_meshes(loader->GetMeshes())
	{
	}

    void Model::Draw(Shader& shader, Camera& camera, glm::mat4 model, glm::vec3 translation, glm::quat rotation, glm::vec3 scale)
    {   
        for (u32 i = m_meshes.size(); i --> 0;)
        {
			m_meshes[i]->Draw(shader, camera, model, translation, rotation, scale);
        }
    }

    std::vector<Ref<Texture>> Model::GetTextures(u32 index)
    {
        return m_meshes[index]->Textures();
    }

	std::vector<Ref<Texture>> Model::GetTextures()
	{
        std::vector<Ref<Texture>> return_textures;

        for (auto& mesh : m_meshes)
        {
            for (auto& texture : mesh->Textures())
            {
				return_textures.push_back(texture);
            }
        }

        return return_textures;
	}

}
