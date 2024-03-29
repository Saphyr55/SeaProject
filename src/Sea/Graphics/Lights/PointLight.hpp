#pragma once

#include "Sea/Graphics/Lights/Light.hpp"
#include "Sea/Graphics/Shaders/Shader.hpp"

namespace Sea
{
	class PointLight : public Light
	{
	public:
		f32 Constant = 1.0f;
		f32 Linear = 0.22f;
		f32 Quadratic = 0.20f;

		void Draw(Shader& shader);

		PointLight()
		{ 
			if (!ids.empty()) id = ids.back() + 1;
			else id = 0;
			ids.push_back(id);
			light = "pointLights[" + std::to_string(id) + "]";
		};
		~PointLight() = default;

	private:
		static std::vector<u32> ids;
	};

	std::vector<u32> PointLight::ids;

	void PointLight::Draw(Shader& shader)
	{	
		shader.Use();
		shader.SetInt("sizePointLight", ids.size());
		shader.SetVec3f(light + ".diffuse", Diffuse);
		shader.SetVec3f(light + ".specular", Specular);
		shader.SetVec3f(light + ".position", Position);
		shader.SetVec3f(light + ".ambient", Ambient);
		shader.SetFloat(light + ".constant", Constant);
		shader.SetFloat(light + ".linear", Linear);
		shader.SetFloat(light + ".quadratic", Quadratic);
	}

} // namespace Sea
