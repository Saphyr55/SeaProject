#pragma once

#include <memory>
#include <vector>
#include <Sea/Core/Common.hpp>

namespace Sea
{
	class GLElementBuffer
	{
	public:
		void Bind();
		void Unbind();
		void Delete();

		GLElementBuffer(std::vector<u32>& indices);
		~GLElementBuffer()=default;

	private:
		u32 id;
	};

	using GLElementBufferPtr = std::shared_ptr<GLElementBuffer>;

}