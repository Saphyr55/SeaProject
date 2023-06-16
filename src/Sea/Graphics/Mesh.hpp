#pragma once

#include <memory>
#include <vector>

#include "Sea/Core/Common.hpp"
#include "Sea/Graphics/Texture.hpp"
#include "Sea/Graphics/Vertex.hpp"
#include "Sea/Graphics/Shaders/Shader.hpp"
#include "Sea/Graphics/Rendering/Camera.hpp"

namespace Sea
{

	class Mesh
	{
	SEA_PROPERTY_READONLY(Textures, std::vector<Ref<Texture>>, m_textures)
	SEA_PROPERTY_READONLY(Indices, std::vector<u32>, m_indices)
	SEA_PROPERTY_READONLY(Vertices, std::vector<Vertex>, m_vertices)

	public:
		virtual void Draw(Shader& shader) = 0;
		virtual void Draw(Shader& shader, Camera& camera, 
			glm::mat4 model = glm::mat4(1.0f),
			glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
			glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
		) = 0;

	public:
		Mesh(std::vector<Vertex>& vertices, std::vector<u32>& indices, std::vector<Ref<Texture>>& textures);
		Mesh(std::vector<Vertex>& vertices, std::vector<u32>& indices);

	protected:
		void SetupTextures(Shader& shader);
	};

	using RMesh = Ref<Mesh>;

}

