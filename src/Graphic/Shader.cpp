#include "Sea/Graphic/Shader.hpp"
#include "Sea/Core/Factory.hpp"

namespace Sea
{


	Ref<Shader> Shader::New(std::string_view vertexShaderSource, std::string_view fragmentShaderSource)
	{
		return Factory::CreateShader(vertexShaderSource, fragmentShaderSource);
	}

}