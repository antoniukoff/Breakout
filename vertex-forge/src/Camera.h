#pragma once

#include "math/vec3.h"
#include "math/mat4.h"

class EventSystem;

class Camera
{
public:
	Camera(vec3 eye, vec3 to, vec3 up);

	void register_key_events(EventSystem& system);
	void register_mouse_events(EventSystem& system);

	void update();

	const mat4& get_view_matrix();
	const vec3& get_position() const;

private:
	void rotate_camera();

private:
	bool  m_is_rotating = false;
	vec3  m_on_drag_begin;
	vec3  m_on_drag;
	float yaw = 0.0f, pitch = 0.0f;

	// Movement speed and key states
	float move_speed = 0.1f;
	bool move_forward = false;
	bool move_backward = false;
	bool move_left = false;
	bool move_right = false;

	vec3 m_camera_pos;
	vec3 m_target;
	vec3 m_up;

	bool m_is_dirty = true;
	mat4 m_view_matrix;
};

