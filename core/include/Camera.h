#pragma once

#include "math/vec3.h"
#include "math/mat4.h"

class Camera
{
public:
	Camera();

	void init_view(vec3 from, vec3 at, vec3 up);
	void init_projection(float aspect_ratio, float fov, float near, float far);

	virtual void update();

	const vec3& get_position() const;
	const vec3& get_look_dir() const;
	const vec3& get_target_pos() const;
	void set_position(const vec3& position);
	void set_target(const vec3& position);

	void follow(const vec3& position);

	const mat4& get_view_matrix();
	const mat4& get_projection_matrix() const 
	{
		return m_projection_matrix;
	}

protected:
	vec3 m_camera_pos;
	vec3 m_target;
	vec3 m_up;

	bool m_is_dirty = false;

	/// Rotation
	float yaw = 0.0f, pitch = 0.0f, roll = 0.0f;

	// Movement
	float move_speed = 0.1f;

private:
	mat4 m_view_matrix;
	mat4 m_projection_matrix;
};

