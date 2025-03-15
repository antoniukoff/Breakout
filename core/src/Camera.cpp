#include "Camera.h"
#include "Input.h"

Camera::Camera()
{}

void Camera::init_view(vec3 from, vec3 at, vec3 up)
{
	m_camera_pos = from;
	m_target = at;
	m_up = up;
	m_view_matrix = mat4::calculate_view_matrix(from, at, up);
}

void Camera::init_projection(float aspect_ratio, float fov, float near, float far)
{
	m_projection_matrix = mat4::calculate_projection(aspect_ratio, fov, near, far);
}

const mat4& Camera::get_view_matrix()
{
	if (m_is_dirty)
	{
		m_view_matrix = mat4::calculate_view_matrix(m_camera_pos, m_target, m_up);
		m_is_dirty = false;
	}
	return m_view_matrix;
}

void Camera::update()
{
	rotate_camera();

	vec3 forward = vec3::normalize(m_target - m_camera_pos);
	vec3 right = vec3::normalize(vec3::cross(forward, m_up));

	vec3 move_direction = {};
	if (Input::is_key_pressed(GLFW_KEY_W))
		move_direction += forward;
	if (Input::is_key_pressed(GLFW_KEY_S))
		move_direction -= forward;
	if (Input::is_key_pressed(GLFW_KEY_D))
		move_direction += right;
	if (Input::is_key_pressed(GLFW_KEY_A))
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
