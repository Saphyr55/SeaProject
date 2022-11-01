#include <Sea/Graphic/Mesh.hpp>
#include <Sea/Graphic/Shader.hpp>

namespace Sea
{
	Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<u32>& indices, std::vector<Ref<Texture>>& textures) :
		m_vertices(m_vertices),
		m_indices(indices), 
		m_textures(textures)
	{

	}

	Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<u32>& indices) :
		m_vertices(m_vertices),
		m_indices(indices)
	{
	}

	void Mesh::SetupTextures(Shader& shader)
	{	
		u32 numDiffuse = 0;
		u32 numSpecular = 0;

		for (u32 i = 0; i < m_textures.size(); i++)
		{
			std::string num;
			std::string type;
			Texture::Type textureType = m_textures[i]->TextureType;
			switch (textureType)
			{
			case Texture::Type::Diffuse:
				type = "diffuse";
				num = std::to_string(numDiffuse++);
				break;
			case Texture::Type::Specular:
				type = "specular";
				num = std::to_string(numDiffuse++);
				break;
			default:
				break;
			}
			shader.Set1Int(std::string("material." + type + num), i);
			m_textures[i]->Bind();
		}
	}
}
