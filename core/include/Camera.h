#pragma once

#include "math/vec3.h"
#include "math/mat4.h"

struct camera_params
{
	vec3 from = { 0.0f, 0.0f, 0.5f };
	vec3 at   = { 0.0f, 0.0f, 0.0f };
	vec3 up   = { 0.0f, 1.0f, 0.0f };
	float fov = 90.0f, near = 0.1f, far = 1000.0f;
};

class camera
{
public:
	camera(camera_params params = camera_params());

	virtual void update(float dt);

	const vec3& get_position() const;
	const vec3& get_target_pos() const;
	const vec3 get_look_dir() const;

	void set_position(const vec3& position);
	void set_target(const vec3& position);

	const mat4& get_view_matrix(float interval);
	const mat4& get_projection_matrix() const {	return m_projection_matrix; }

private:
	void rotate();

	void init_view(vec3 from, vec3 at, vec3 up);
	void init_projection(float aspect_ratio, float fov, float near, float far);

protected:
	camera_params m_params;

	/// Rotation and movement
	float yaw = 0.0f, pitch = 0.0f;
	vec3 m_look_dir;

	float move_speed = 10.0f;

	bool m_is_dirty = false;

	float prev_x, prev_y;
	bool mouse_pressed = false;

private:
	mat4 m_view_matrix;
	mat4 m_projection_matrix;
};

