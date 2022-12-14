#include "Sea/Backend/OpenGL/GLMesh.hpp"
#include "Sea/Backend/OpenGL/GL.hpp"
#include "Sea/Graphic/Vertex.hpp"
#include "Sea/Graphic/Shader.hpp"
#include "Sea/Graphic/Texture.hpp"
#include "Sea/Backend/OpenGL/GLElementBuffer.hpp"
#include "Sea/Backend/OpenGL/GLVertexBuffer.hpp"

#include <mcl/Logger.hpp>

using mcl::Log;

namespace Sea::Backend::OpenGL
{

	void GLMesh::Draw(Shader& shader, Camera& camera, glm::mat4 model, glm::vec3 translation, glm::quat rotation, glm::vec3 scale)
	{		
		shader.Use();
		shader.SetMatrix4fv("cameraProjectionView", camera.ProjectionView);
		shader.SetVec3f("cameraPos", camera.Position);
		vao.Bind();
		SetupTextures(shader);

		model = glm::translate(model, translation);
		model = glm::scale(model, scale);

		shader.SetMatrix4fv("model", model * glm::mat4_cast(rotation));

		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	}

	GLMesh::GLMesh(std::vector<Vertex>& vertices, std::vector<u32>& indices) :
		Mesh(vertices, indices)
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

	GLMesh::GLMesh(std::vector<Vertex>& vertices, std::vector<u32>& indices, std::vector<Mold<Texture>>& textures) :
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