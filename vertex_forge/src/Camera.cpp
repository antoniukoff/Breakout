#include "Camera.h"
#include "EventSystem.h"
#include <GLFW/glfw3.h>

Camera::Camera(vec3 eye, vec3 to, vec3 up) : 
	m_camera_pos(eye)
	, m_target(to)
	, m_up(up)
{}

const mat4& Camera::get_view_matrix()
{
	if (m_is_dirty)
	{
		m_view_matrix = mat4::calculate_view_matrix(m_camera_pos, m_target, m_up);
		m_is_dirty = false;
	}
	return m_view_matrix;
}

void Camera::register_key_events(EventSystem& system)
{
	// W key
	system.register_key_event(GLFW_KEY_W, GLFW_PRESS,
		[&](int key, int action, int x, int y)
		{
			move_forward = true;
		});
	system.register_key_event(GLFW_KEY_W, GLFW_RELEASE,
		[&](int key, int action, int x, int y)
		{
			move_forward = false;
		});

	// S key
	system.register_key_event(GLFW_KEY_S, GLFW_PRESS,
		[&](int key, int action, int x, int y)
		{
			move_backward = true;
		});
	system.register_key_event(GLFW_KEY_S, GLFW_RELEASE,
		[&](int key, int action, int x, int y)
		{
			move_backward = false;
		});

	// A key
	system.register_key_event(GLFW_KEY_A, GLFW_PRESS,
		[&](int key, int action, int x, int y)
		{
			move_left = true;
		});
	system.register_key_event(GLFW_KEY_A, GLFW_RELEASE,
		[&](int key, int action, int x, int y)
		{
			move_left = false;
		});

	// D key
	system.register_key_event(GLFW_KEY_D, GLFW_PRESS,
		[&](int key, int action, int x, int y)
		{
			move_right = true;
		});
	system.register_key_event(GLFW_KEY_D, GLFW_RELEASE,
		[&](int key, int action, int x, int y)
		{
			move_right = false;
		});
}

void Camera::register_mouse_events(EventSystem& system)
{
	system.register_mouse_event(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS,
		[&](int key, int action, double x, double y)
		{
			m_is_rotating = true;
			auto [rel_x, rel_y] = system.get_rel_mouse_pos();
			m_on_drag_begin = { rel_x, rel_y, 0.0f };
		});

	system.register_mouse_event(GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE,
		[&](int key, int action, double x, double y)
		{
			m_is_rotating = false;

			vec3 on_drag_end = m_on_drag - m_on_drag_begin;

			yaw += on_drag_end.x;
			pitch += on_drag_end.y;

			m_on_drag_begin = {};
			m_on_drag = {};
		});

	system.register_mouse_moved_event(typeid(this).hash_code(), 1,
		[&](int key, int action, int x, int y)
		{
			auto [rel_x, rel_y] = system.get_rel_mouse_pos();
			m_on_drag = { rel_x, rel_y, 0.0f };
		});
}

void Camera::update()
{
	rotate_camera();

	vec3 forward = vec3::normalize(m_target - m_camera_pos);
	vec3 right = vec3::normalize(vec3::cross(forward, m_up));

	vec3 move_direction = {};
	if (move_forward)
		move_direction += forward;
	if (move_backward)
		move_direction -= forward;
	if (move_right)
		move_direction += right;
	if (move_left)
		move_direction -= right;

	if (move_direction.mag() > 0.0f)
	{
		m_is_dirty = true;

		m_camera_pos += move_direction * move_speed;
		m_target += move_direction * move_speed;
	}
}

const vec3& Camera::get_position() const
{
	return m_camera_pos;
}

void Camera::rotate_camera()
{
	if (!m_is_rotating)
	{
		return;
	}

	vec3 look_dir = { 0.0f, 0.0f, -1.0f };

	vec3 rotation_dir = m_on_drag - m_on_drag_begin;

	float curr_yaw	 = yaw + rotation_dir.x;
	float curr_pitch = pitch + rotation_dir.y;

	mat4 m_yaw		= mat4::rotate_y(curr_yaw, false);
	mat4 m_pitch	= mat4::rotate_x(curr_pitch, false);
	mat4 m_combined = mat4::mult_mat_by_mat(m_yaw, m_pitch);
	mat4::mult_vec_by_mat(m_combined, look_dir);

	m_target	= m_camera_pos + look_dir;
	m_is_dirty	= true;
}
