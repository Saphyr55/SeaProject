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

		GLShader(File /*vertexFragment*/, File /*fragmentShader*/);
		GLShader(std::string /*vertexShaderSource*/, std::string /*fragmentShaderSource*/);
		GLShader(const GLShader&) = default;
		GLShader(GLShader&&) = default;
		~GLShader()=default;

	private:
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