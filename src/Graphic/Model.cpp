#include <Sea/Graphic/Model.hpp>

namespace Sea
{

    Model::Model(Ref<ILoader> loader) : m_loader(loader)
    {

    }

    void Model::Draw(Shader& shader, Camera& camera)
    {
		for (u32 i = 0; i < m_loader->GetMeshes().size(); i++)
            m_loader->GetMeshes()[i]->Draw(shader, camera, m_loader->GetmatricesMeshes()[i]);
    }

}
