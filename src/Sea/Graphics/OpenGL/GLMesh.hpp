#pragma once

#include "Sea/Graphics/Mesh.hpp"
#include "Sea/Graphics/OpenGL/GLVertexArray.hpp"

namespace Sea
{	
	class GLMesh : public Mesh
	{
	public:
		void Draw(Shader& shader, Camera& camera,
			glm::mat4 model			= glm::mat4(1.0f),
			glm::vec3 translation	= glm::vec3(0.0f, 0.0f, 0.0f),
			glm::quat rotation		= glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
			glm::vec3 scale			= glm::vec3(1.0f, 1.0f, 1.0f)
		) override;
		void Draw(Shader& shader) override;

	public:
		GLMesh(std::vector<Vertex>& vertices, std::vector<u32>& indices, std::vector<Ref<Texture>>& textures);
		GLMesh(std::vector<Vertex>& vertices, std::vector<u32>& indices);

	private:
		GLVertexArray vao;

	};

}