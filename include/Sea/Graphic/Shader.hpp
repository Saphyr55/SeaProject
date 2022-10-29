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
		virtual u32 GetId() = 0;
	};

	using ShaderPtr = std::shared_ptr<Shader>;

}