#pragma once

#include <memory>
#include <vector>

#include "Sea/Core/Clock.hpp"
#include "Sea/Common/CommonType.hpp"
#include "Sea/Graphic/Texture.hpp"
#include "Sea/Graphic/Vertex.hpp"
#include "Sea/Renderer/Camera.hpp"
#include "Sea/Graphic/Shader.hpp"

namespace Sea
{

	class Mesh
	{
	public:

		void AddHandler(Handler<Clock&> handler);

		virtual void Draw(Shader& shader, Camera& camera, 
			glm::mat4 model = glm::mat4(1.0f),
			glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
			glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
		) = 0;

		inline std::vector<Mold<Texture>> GetTextures() { return m_textures; }
		inline std::vector<u32> GetIndices() { return m_indices; }
		inline std::vector<Vertex> GetVertices() { return m_vertices; }

		Mesh(std::vector<Vertex>& vertices, std::vector<u32>& indices, std::vector<Mold<Texture>>& textures);
		Mesh(std::vector<Vertex>& vertices, std::vector<u32>& indices);

	protected:
		void SetupTextures(Shader& shader);

	protected:
		std::vector<Handler<Clock&>> handlers;
		std::vector<Vertex> m_vertices;
		std::vector<u32> m_indices;
		std::vector<Mold<Texture>> m_textures;
	};

	using RMesh = Ref<Mesh>;

}

