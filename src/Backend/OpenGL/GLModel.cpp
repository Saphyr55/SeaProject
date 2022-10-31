#include <Sea/Backend/OpenGL/GLModel.hpp>

namespace Sea::Backend::OpenGL
{
    GLModel::GLModel(GLTFLoader gltfLoader) : 
        m_gltfLoader(gltfLoader)
    {

    }

    GLModel::~GLModel()
    {
    }
}
