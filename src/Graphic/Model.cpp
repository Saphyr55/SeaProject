#include <Sea/Graphic/Model.hpp>

namespace Sea
{

	Model::Model(std::vector<Mold<Mesh>> meshes, std::vector<glm::mat4> matricesMeshes) : 
        matricesMeshes(matricesMeshes), meshes(meshes)
	{
	}

	Model::Model(std::vector<Mold<Mesh>> meshes) :
		 meshes(meshes)
	{
	}

	Model::Model(Ref<IModelLoader> loader) : matricesMeshes(loader->GetMatricesMeshes()), meshes(loader->GetMeshes())
	{
	}

    void Model::Draw(Shader& shader, Camera& camera, glm::mat4 model, glm::vec3 translation, glm::quat rotation, glm::vec3 scale)
    {   
        for (u32 i = meshes.size(); i --> 0;)
        {
			meshes[i]->Draw(shader, camera, model, translation, rotation, scale);
        }
    }

    std::vector<Mold<Texture>> Model::GetTextures(u32 index)
    {
        return meshes[index]->GetTextures();
    }

	std::vector<Mold<Texture>> Model::GetTextures()
	{
        std::vector<Mold<Texture>> return_textures;

        for (auto& mesh : meshes)
        {
            for (auto& texture : mesh->GetTextures())
            {
				return_textures.push_back(texture);
            }
        }

        return return_textures;
	}

}
