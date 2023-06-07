#pragma once

#include "Sea/Graphic/Light.hpp"
#include "Sea/Graphic/Shaders/Shader.hpp"

#include <mcl/Logger.hpp>

using mcl::Log;

namespace Sea
{
	class SpotLight : public Light
	{
	public:
		glm::vec3 Direction = glm::vec3(0.0, 1.0, 0.0);
		f32 Constant = 1.0f;
		f32 Linear = 0.22f;
		f32 Quadratic = 0.20f;
		f32 InnerDegree = 12.5f;
		f32 OuterDegree = 17.5f;

		void Draw(Shader& shader);

		SpotLight() 
		{
			if (!ids.empty()) id = ids.back() + 1;
			else id = 0;
			ids.push_back(id);
			light = "spotLights[" + std::to_string(id) + "]";
		};
		~SpotLight() = default;

	private:
		static std::vector<u32> ids;
	};
	std::vector<u32> SpotLight::ids;

	void SpotLight::Draw(Shader& shader)
	{	
		shader.Use();
		shader.SetInt("sizeSpotLight", ids.size());
		shader.SetVec3f(light + ".ambient", Ambient);
		shader.SetVec3f(light + ".diffuse", Diffuse);
		shader.SetVec3f(light + ".specular", Specular);
		shader.SetVec3f(light + ".direction", Direction);
		shader.SetVec3f(light + ".position", Position);
		shader.SetFloat(light + ".constant", Constant);
		shader.SetFloat(light + ".linear", Linear);
		shader.SetFloat(light + ".quadratic", Quadratic);
		shader.SetFloat(light + ".cutOff", glm::cos(glm::radians(InnerDegree)));
		shader.SetFloat(light + ".outerCutOff", glm::cos(glm::radians(OuterDegree)));
	}

} // namespace Sea
