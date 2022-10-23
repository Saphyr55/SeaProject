#pragma once

#include <memory>
#include <glm/glm.hpp>


namespace Sea
{	
	class Mouse final
	{
		
		using MousePtr = std::shared_ptr<const Mouse>;

	public:
		static glm::uvec2 GetPos();
		static glm::vec2 GetRelativePos();

	private:
		void Update() const;

	private:
		glm::uvec2 pos;
		glm::vec2 relativePos;
		static MousePtr instancePtr;
	};
}