#pragma once

#include "Sea/Graphic/Light.hpp"
#include "Sea/Graphic/Shader.hpp"

namespace Sea
{
	class PointLight : public Light
	{
	public:
		f32 Constant = 1.0f;
		f32 Linear = 0.35f;
		f32 Quadratic = 0.44f;

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
		shader.Set1Int("sizePointLight", ids.size());
		shader.SetVec3f(light + ".diffuse", Diffuse);
		shader.SetVec3f(light + ".specular", Specular);
		shader.SetVec3f(light + ".position", Position);
		shader.SetVec3f(light + ".ambient", Ambient);
		shader.SetFloat(light + ".constant", Constant);
		shader.SetFloat(light + ".linear", Linear);
		shader.SetFloat(light + ".quadratic", Quadratic);
	}

} // namespace Sea
