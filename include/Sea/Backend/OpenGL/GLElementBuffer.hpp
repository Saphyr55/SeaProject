#pragma once

#include <memory>
#include <Sea/Common/CommonType.hpp>

namespace Sea::Backend::OpenGL
{
	class GLElementBuffer
	{
	public:
		void Bind();
		void Unbind();
		void Delete();

		GLElementBuffer(u32 indices[], u32 size);
		~GLElementBuffer()=default;

	private:
		u32 id;
	};

	using GLElementBufferPtr = std::shared_ptr<GLElementBuffer>;

}