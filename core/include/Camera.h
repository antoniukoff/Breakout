#pragma once

#include "math/vec3.h"
#include "math/mat4.h"

class Camera
{
public:
	Camera();

	void init_view(vec3 from, vec3 at, vec3 up);
	void init_projection(float aspect_ratio, float fov, float near, float far);

	void update();

	const mat4& get_view_matrix();
	const vec3& get_position() const;

	mat4 get_projection_matrix()
	{
		return m_projection_matrix;
	}
private:
	void rotate_camera();

private:
	vec3 m_camera_pos;
	vec3 m_target;
	vec3 m_up;

	mat4 m_view_matrix;
	mat4 m_projection_matrix;

	bool m_is_dirty = true;

	/// Rotation
	bool  m_is_rotating = false;
	vec3  m_on_drag_begin;
	vec3  m_on_drag;
	float yaw = 0.0f, pitch = 0.0f;

	// Movement
	float move_speed = 0.1f;
	
};

