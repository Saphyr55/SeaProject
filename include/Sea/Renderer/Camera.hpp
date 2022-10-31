#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Sea/Common/CommonType.hpp"

namespace Sea
{
	class Camera
	{
	public:
		glm::mat4 ProjectionView;
		glm::vec3 Target = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Position;
		glm::vec3 Right;
		s32 Width, Height;
		f32 Yaw, Pitch, Roll = 0;

		Camera(s32 width, s32 height, glm::vec3 position);
		~Camera() = default;

		void SetOrientation(f32 Yaw, f32 Pitch);
		void SetViewProjection(f32 fov, f32 zNear, f32 zFar);
	};
}