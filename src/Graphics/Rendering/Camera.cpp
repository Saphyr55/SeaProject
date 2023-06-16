#include "Sea/Graphics/Rendering/Camera.hpp"

namespace Sea
{

	Camera::Camera(s32 width, s32 height, glm::vec3 position)
		:Position(position), Width(width), Height(height), Yaw(-90), Pitch(0)
	{
		Right = glm::normalize(glm::cross(Up, Orientation));
	}

	void Camera::SetViewProjection(f32 fov, f32 zNear, f32 zFar)
	{
		ProjectionView =
			glm::perspective(glm::radians(fov), (f32)((f32)Width / (f32)Height), zNear, zFar) * // projection
			glm::lookAt(Position, Position + Orientation, Up); // view
	}

	void Camera::SetOrientation(f32 yaw, f32 pitch)
	{
		Yaw = yaw;
		Pitch = pitch;
		glm::vec3 new_orientation;
		new_orientation.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		new_orientation.y = -sin(glm::radians(Pitch));
		new_orientation.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Orientation = glm::normalize(new_orientation);
	}
}