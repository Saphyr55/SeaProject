#include "Sea/Backend/OpenGL/GLMesh.hpp"
#include "Sea/Backend/OpenGL/GL.hpp"
#include <mcl/Logger.hpp>

using mcl::Log;

namespace Sea::Backend::OpenGL
{

	void GLMesh::Draw(Shader& shader, Camera& camera, glm::mat4 matrix, glm::vec3 translation, glm::quat rotation, glm::vec3 scale)
	{		
		shader.Use();
		shader.SetMatrix4fv("cameraProjectionView", camera.ProjectionView);
		shader.SetVec3f("cameraPos", camera.Position);
		vao.Bind();
		SetupTextures(shader);

		// Initialize matrices
		glm::mat4 trans = glm::mat4(1.0f);
		glm::mat4 rot = glm::mat4(1.0f);
		glm::mat4 sca = glm::mat4(1.0f);

		// Transform the matrices to their correct form
		trans = glm::translate(trans, translation);
		rot = glm::mat4_cast(rotation);
		sca = glm::scale(sca, scale);

		// Push the matrices to the vertex shader
		shader.SetMatrix4fv("translation", trans);
		shader.SetMatrix4fv("rotation", rot);
		shader.SetMatrix4fv("scale", sca);
		shader.SetMatrix4fv("model", matrix);

		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	}

	GLMesh::GLMesh(std::vector<Vertex>& vertices, std::vector<u32>& indices, std::vector<Ref<Texture>>& textures) :
		Mesh(vertices, indices, textures)
	{
		vao.Bind();
		GLVertexBuffer vbo(vertices);
		GLElementBuffer ebo(indices);

		vao.LinkVertexBuffer(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
		vao.LinkVertexBuffer(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(f32)));
		vao.LinkVertexBuffer(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(f32)));
		vao.LinkVertexBuffer(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(f32)));

		vao.Unbind();
		vbo.Unbind();
		ebo.Unbind();
	}


}