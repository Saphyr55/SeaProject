#pragma once

#include "Sea/Graphic/Mesh.hpp"
#include "Sea/Backend/OpenGL/GLVertexArray.hpp"

namespace Sea
{
	class Texture;
	class Shader;
	class Camera;
	struct Vertex;
}

namespace Sea::Backend::OpenGL
{	

	class GLMesh : public Mesh
	{
	public:
		void Draw(Shader& shader, Camera& camera,
			glm::mat4 model = glm::mat4(1.0f),
			glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
			glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
		) override;

		GLMesh(std::vector<Vertex>& vertices, std::vector<u32>& indices, std::vector<Mold<Texture>>& textures);
		GLMesh(std::vector<Vertex>& vertices, std::vector<u32>& indices);

	private:
		GLVertexArray vao;

	};

}