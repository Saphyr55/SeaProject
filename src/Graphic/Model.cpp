#include <Sea/Graphic/Model.hpp>

namespace Sea
{

    Model::Model(Ref<IModelLoader> loader) : matricesMeshes(loader->GetMatricesMeshes()), meshes(loader->GetMeshes())
    {
    }

	Model::Model(std::vector<Mold<Mesh>> meshes, std::vector<glm::mat4> matricesMeshes) : 
        matricesMeshes(matricesMeshes), meshes(meshes)
	{
	}
    
    void Model::Draw(Shader& shader, Camera& camera, glm::vec3 translation, glm::quat rotation, glm::vec3 scale)
    {   
	    for (u32 i = 0; i < meshes.size(); i++)
            meshes[i]->Draw(shader, camera, matricesMeshes[i], translation, rotation);
    }

}
