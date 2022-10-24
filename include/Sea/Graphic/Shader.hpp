#pragma once

#include <Sea/Common/File.hpp>
#include <Sea/Common/CommonType.hpp>

namespace Sea
{
	class Shader
	{
	public:
		virtual void Use()=0;
		virtual void Delete()=0;

	private:

	};

}