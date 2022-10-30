#pragma once

#include <string>
#include <Sea/Graphic/Shader.hpp>

namespace Sea::Backend::OpenGL
{
	class GLShader final : public Shader
	{
	public:
		void Use();
		void Delete();
		void SetVec4f(std::string uniform, glm::vec4 value);
		void SetVec3f(std::string uniform, glm::vec3 value);
		void Set4Float(std::string uniform, f32 x, f32 y, f32 z, f32 w);
		void SetMatrix4fv(std::string uniform, glm::mat4 value);
		void Set1Int(std::string uniform, s32 value);
		void Set1Float(std::string uniform, f32 value);
		u32 GetId();

		GLShader(File /*vertexFragment*/, File /*fragmentShader*/);
		GLShader(std::string /*vertexShaderSource*/, std::string /*fragmentShaderSource*/);
		GLShader(const GLShader&) = default;
		GLShader(GLShader&&) = default;
		~GLShader()=default;

	private:
		s32 GetUniformLocation(std::string uniform);
		u32 CreateShader(u32 type, char* source);
		bool CheckInfoShader(u32 shader, u32 status);
		bool CheckIngoProgram(u32 status);
		void CreateProgram();

	private:
		char* m_vertexShaderSource;
		char* m_fragmentShaderSource;
		u32 programId;
		
	};

}