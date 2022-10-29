#include "Sea/Backend/OpenGL/GLCamera.hpp"
#include "Sea/Backend/OpenGL/GL.hpp"
#include "Sea/Graphic/Shader.hpp"

namespace Sea::Backend::OpenGL
{
	GLCamera::GLCamera(s32 width, s32 height, glm::vec3 position)
		:Position(position), Width(width), Height(height)
	{
		Right = glm::normalize(glm::cross(Up, Orientation));
	}

	void GLCamera::SetViewProjection(f32 fov, f32 zNear, f32 zFar)
	{
		ProjectionView = 
			glm::perspective(glm::radians(fov), (f32)((f32)Width / (f32)Height), zNear, zFar)* // porjection
			glm::lookAt(Position, Position + Orientation, Up); // view
	}


}