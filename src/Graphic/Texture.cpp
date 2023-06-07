#include "Sea/Graphic/Texture.hpp"
#include "Sea/Core/File.hpp"

namespace Sea
{
    Texture::Texture(File image, Type texType, u32 slot) : 
		imageFile(image),
		TextureType(texType),
		m_slot(slot),
		m_unit(m_slot)
    {
    }

	Texture::Texture(std::string_view path, Type texType, u32 slot) :
		Texture(File(path), texType, slot)
	{
	}

}
