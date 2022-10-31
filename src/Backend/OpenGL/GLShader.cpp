#include "Sea/Backend/OpenGL/GLShader.hpp"
#include "Sea/Backend/OpenGL/GL.hpp"
#include <mcl/Logger.hpp>
#include <glm/gtc/type_ptr.hpp>

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

	void GLShader::Set1UInt(std::string uniform, u32 value)
	{
		glUniform1ui(GetUniformLocation(uniform), value);
	}

	void GLShader::SetVec4f(std::string uniform, glm::vec4 value)
	{
		glUniform4fv(GetUniformLocation(uniform), 1, glm::value_ptr(value));
	}

	void GLShader::SetVec3f(std::string uniform, glm::vec3 value)
	{
		glUniform3fv(GetUniformLocation(uniform), 1, glm::value_ptr(value));
	}

	void GLShader::Set4Float(std::string uniform, f32 x, f32 y, f32 z, f32 w)
	{
		glUniform4f(GetUniformLocation(uniform), x, y, z ,w);
	}

	void GLShader::SetMatrix4fv(std::string uniform, glm::mat4 value)
	{
		glUniformMatrix4fv(GetUniformLocation(uniform), 1, GL_FALSE, glm::value_ptr(value));
	}

	void GLShader::Set1Int(std::string uniform, s32 value)
	{
		glUniform1i(GetUniformLocation(uniform), value);
	}

	void GLShader::Set1Float(std::string uniform, f32 value)
	{
		glUniform1f(GetUniformLocation(uniform), value);
	}

	u32 GLShader::GetId()
	{
		return programId;
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

	s32 GLShader::GetUniformLocation(std::string uniform)
	{
		return glGetUniformLocation(programId, uniform.c_str());
	}
}
