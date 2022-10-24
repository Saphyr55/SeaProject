#include "Sea/Backend/OpenGL/GLShader.hpp"
#include "Sea/Backend/OpenGL/GL.hpp"
#include <mcl/Logger.hpp>

using mcl::Log;

namespace Sea::Backend::OpenGL
{
	void GLShader::Use()
	{
		glUseProgram(programId);
	}

	void GLShader::Delete()
	{
		glDeleteShader(programId);
	}

	GLShader::GLShader(File vertexShader, File fragmentShader)
		: GLShader(vertexShader.Read(), fragmentShader.Read()) 
	{
	}

	GLShader::GLShader(std::string vertexShader, std::string fragmentShader)
		: m_vertexShaderSource((char*)vertexShader.c_str()), m_fragmentShaderSource((char*)fragmentShader.c_str())
	{
		CreateProgram();
	}
	
	u32 GLShader::CreateShader(u32 type, char* source)
	{
		u32 shader;
		shader = glCreateShader(type);
		glShaderSource(shader, 1, &source, NULL);
		glCompileShader(shader);
		return shader;
	}

	bool GLShader::CheckInfoShader(u32 shader, u32 status)
	{
		s32  success;
		char infoLog[512];
		glGetShaderiv(shader, status, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			Log::Error() << "OpengGL Shader : " << infoLog;
		}
		return success;
	}
	
	bool GLShader::CheckIngoProgram(u32 status) 
	{
		s32 success;
		char infoLog[512];
		glGetProgramiv(programId, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(programId, 512, NULL, infoLog);
			Log::Error() << "OpengGL Shader : " << infoLog;
		}
		return success;
	}

	void GLShader::CreateProgram()
	{
		// Vertex Shader
		u32 vertexShader = CreateShader(GL_VERTEX_SHADER, m_vertexShaderSource);
		CheckInfoShader(vertexShader, GL_COMPILE_STATUS);

		// Fragment Shader
		u32 fragmentShader = CreateShader(GL_FRAGMENT_SHADER, m_fragmentShaderSource);
		CheckInfoShader(fragmentShader, GL_COMPILE_STATUS);

		// Shader Program
		programId = glCreateProgram();
		glAttachShader(programId, vertexShader);
		glAttachShader(programId, fragmentShader);
		glLinkProgram(programId);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		CheckIngoProgram(GL_LINK_STATUS);
	}
}
