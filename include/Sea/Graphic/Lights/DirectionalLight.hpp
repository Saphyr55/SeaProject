#pragma once

#include "Sea/Graphic/Light.hpp"
#include "Sea/Graphic/Shader.hpp"

namespace Sea
{
	class DirectionalLight : public Light
	{
	public:
		glm::vec3 Direction = glm::vec3(0.0f, -1.0f, 0.0f);

		void Draw(Shader& shader);

		DirectionalLight() 
		{
			if (!ids.empty()) id = ids.back() + 1;
			else id = 0;
			ids.push_back(id);
			light = "directionalLights[" + std::to_string(id) + "]";
		};
		~DirectionalLight() = default;
	
	private:
		static std::vector<u32> ids;
	};

	std::vector<u32> DirectionalLight::ids;

	void DirectionalLight::Draw(Shader& shader)
	{	
		Position = -Direction;
		shader.Use();
		shader.Set1Int("sizeDirectionalLight", ids.size());
		shader.SetVec3f(light + ".ambient", Ambient);
		shader.SetVec3f(light + ".diffuse", Diffuse);
		shader.SetVec3f(light + ".specular", Specular);
		shader.SetVec3f(light + ".direction", Direction);
	}

} // namespace Sea
