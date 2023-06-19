#pragma once

#include <string>

#include "Sea/Graphics/Shaders/Shader.hpp"

namespace Sea
{
	class GLShader final : public Shader
	{
	public:
		void Use() override;
		void Delete() override;
		void Set1UInt(std::string uniform, u32 value) override;
		void SetVec4f(std::string uniform, glm::vec4 value) override;
		void SetVec4f(std::string uniform, f32 x, f32 y, f32 z, f32 w) override;
		void SetVec3f(std::string uniform, glm::vec3 value) override;
		void SetVec2f(std::string uniform, f32 x, f32 y) override;
		void SetVec3f(std::string uniform, f32 x, f32 y, f32 z) override;
		void SetMatrix4fv(std::string uniform, glm::mat4 value) override;
		void SetInt(std::string uniform, s32 value) override;
		void SetBool(std::string uniform, bool value) override;
		void SetFloat(std::string uniform, f32 value) override;
		u32 GetId() override;

	public:
		GLShader(File vertexFragment, File fragmentShader);
		GLShader(std::string vertexShaderSource, std::string fragmentShaderSource);
		GLShader(const GLShader &) = default;
		GLShader(GLShader &&) = default;
		~GLShader();

	private:
		s32 GetUniformLocation(std::string uniform);
		u32 CreateShader(u32 type, const char *source);
		bool CheckInfoShader(u32 shader, u32 status);
		bool CheckIngoProgram(u32 status);
		void CreateProgram();

	private:
		const char *m_vertexShaderSource;
		const char *m_fragmentShaderSource;
		u32 programId;
	};

}