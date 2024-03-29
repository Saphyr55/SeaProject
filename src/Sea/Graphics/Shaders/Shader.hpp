#pragma once

#include <Sea/Core/File.hpp>
#include "Sea/Core/Common.hpp"

#include <glm/glm.hpp>

namespace Sea
{

	class Shader
	{
	public:
		virtual void Use() = 0;
		virtual void Delete() = 0;
		virtual void Set1UInt(std::string uniform, u32 value) = 0;
		virtual void SetMatrix4fv(std::string uniform, glm::mat4 value) = 0;
		virtual void SetVec4f(std::string uniform, glm::vec4 value) = 0;
		virtual void SetVec3f(std::string uniform, glm::vec3 value) = 0;
		virtual void SetVec2f(std::string uniform, f32 x, f32 y) = 0;
		virtual void SetVec3f(std::string uniform, f32 x, f32 y, f32 z) = 0;
		virtual void SetVec4f(std::string uniform, f32 x, f32 y, f32 z, f32 w) = 0;
		virtual void SetInt(std::string uniform, s32 value) = 0;
		virtual void SetFloat(std::string uniform, f32 value) = 0;
		virtual void SetBool(std::string uniform, bool value) = 0;
		virtual u32 GetId() = 0;
	};

	using ShaderRef = Ref<Shader>;
	
}