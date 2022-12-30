#include "Sea/Graphic/Texture2D.hpp"
#include "Sea/Common/File.hpp"

namespace Sea
{
    Texture2D::Texture2D(File image, Type texType, u32 slot) : 
		imageFile(image),
		TextureType(texType),
		m_slot(slot),
		m_unit(m_slot)
    {
    }

	Texture2D::Texture2D(std::string_view path, Type texType, u32 slot) :
		Texture2D(File(path), texType, slot)
	{
	}

}
