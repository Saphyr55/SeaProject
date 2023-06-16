#include "Sea/Graphics/Mesh.hpp"
#include "Sea/Graphics/Shaders/Shader.hpp"

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
		u32 numAmbient = 0;
		u32 numShininess = 0;

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
				shader.SetInt(std::string("material." + type + num), i);
				break;

			case Texture::Type::Specular:
				type = "specular";
				num = std::to_string(numSpecular++);
				shader.SetInt(std::string("material." + type + num), i);
				break;

			case Texture::Type::Ambient:
				type = "ambient";
				num = std::to_string(numAmbient++);
				shader.SetInt(std::string("material." + type + num), i);
				break;

			case Texture::Type::Shininess:
				type = "shininess";
				num = std::to_string(numShininess++);
				shader.SetFloat(std::string("material." + type + num), 32);
 				break;

			default:
				break;
			}
			m_textures[i]->Bind();
		}
	}
}
