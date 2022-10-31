#include "Sea/Graphic/Texture.hpp"
#include "Sea/Common/File.hpp"

namespace Sea
{
    Texture::Texture(File image, Type texType, u32 slot) : 
		imageFile(image),
		TextureType(texType),
		m_slot(slot),
		m_unit(m_slot)
    {
    }

}
