#pragma once

#include <vector>
#include <Sea/Graphic/Mesh.hpp>
#include <Sea/Graphic/Vertex.hpp>
#include <Sea/Backend/OpenGL/GLTexture.hpp>
#include <Sea/Graphic/Shader.hpp>
#include "Sea/Backend/OpenGL/GLElementBuffer.hpp"
#include "Sea/Backend/OpenGL/GLShader.hpp"
#include "Sea/Backend/OpenGL/GLVertexArray.hpp"
#include "Sea/Backend/OpenGL/GLVertexBuffer.hpp"

namespace Sea::Backend::OpenGL
{
	class GLMesh : public Mesh
	{
	public:
		void Draw(Shader& shader, Camera& camera,
			glm::mat4 matrix = glm::mat4(1.0f),
			glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
			glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
		) override;

		GLMesh(std::vector<Vertex>& vertices, std::vector<u32>& indices, std::vector<Ref<Texture>>& textures);

	private:
		GLVertexArray vao;

	};

	using GLMeshPtr = Ref<GLMesh>;

}