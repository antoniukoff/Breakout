#include "Camera.h"

#include "InputHandler.h"
#include "Application.h"

#include <algorithm>
#include <iostream>

Camera::Camera(CameraParams params)
	: m_params(params)
{
	init_view(params.from, params.at, params.up);

	float ar = Application::get().get_window()->get_aspect_ratio();
	init_projection(ar, params.fov, params.near, params.far);
}

void Camera::init_view(vec3 from, vec3 at, vec3 up)
{
	m_view_matrix = mat4::calculate_view_matrix(from, at, up);
}

void Camera::init_projection(float aspect_ratio, float fov, float near, float far)
{
	m_projection_matrix = mat4::calculate_projection(aspect_ratio, fov, near, far);
}

const mat4& Camera::get_view_matrix(float interval)
{
	if (m_is_dirty)
	{
		const vec3& from = m_params.from;
		const vec3& at = m_params.at;
		const vec3& up = m_params.up;

		m_view_matrix = mat4::calculate_view_matrix(from, at, up);
		m_is_dirty = false;
	}
	return m_view_matrix;
}

void Camera::update(float dt)
{
	rotate();

	vec3& from = m_params.from;
	vec3& at = m_params.at;
	vec3& up = m_params.up;

	vec3 forward = vec3::normalize(at - from);
	vec3 right = vec3::normalize(vec3::cross(forward, up));

	vec3 move_direction = {};
	if (InputHandler::is_key_pressed(KeyCode::W))
		move_direction += forward;
	if (InputHandler::is_key_pressed(KeyCode::S))
		move_direction -= forward;
	if (InputHandler::is_key_pressed(KeyCode::D))
		move_direction += right;
	if (InputHandler::is_key_pressed(KeyCode::A))
		move_direction -= right;

	if (move_direction.mag() > 0.0f)
	{
		m_is_dirty = true;

		from += move_direction * move_speed * dt;
		at += move_direction * move_speed * dt;
	}
}

void Camera::rotate()
{
	if (InputHandler::is_mouse_pressed(MouseButton::RIGHT))
	{
		m_is_dirty = true;

		auto [screen_mouse_x, screen_mouse_y] = InputHandler::get_rel_mouse_pos();

		if (!mouse_pressed)
		{
			prev_x = screen_mouse_x;
			prev_y = screen_mouse_y;
			mouse_pressed = true;
		}

		float delta_yaw = prev_x - screen_mouse_x + yaw;
		float delta_pitch = prev_y - screen_mouse_y + pitch;

		delta_pitch = std::clamp(delta_pitch, TO_RAD(-89.9f), TO_RAD(89.9f));


		mat4 rotation_m = mat4::rotate_y(delta_yaw, false) * mat4::rotate_x(delta_pitch, false);
		
		vec3 look_dir = vec3{ 0.0f,0.0f,0.0f } - vec3{ 0.0f,0.0f,0.5f };
		mat4::mult_vec_by_mat(rotation_m, look_dir);

		set_target(get_position() + look_dir);
	}
	else
	{
		if (mouse_pressed)
		{
			auto [screen_mouse_x, screen_mouse_y] = InputHandler::get_rel_mouse_pos();
			float delta_x = prev_x - screen_mouse_x;
			float delta_y = prev_y - screen_mouse_y;

			yaw += delta_x;
			pitch += delta_y;

			pitch = std::clamp(pitch, TO_RAD(-89.9f), TO_RAD(89.9f));

			mouse_pressed = false;
		}
	}
}

const vec3& Camera::get_position() const
{
	return m_params.from;
}

const vec3& Camera::get_look_dir() const
{
	return m_params.at - m_params.from;
}

const vec3& Camera::get_target_pos() const
{
	return m_params.at;
}

void Camera::set_position(const vec3& position)
{
	m_params.from = position;
	m_is_dirty = true;
}

void Camera::set_target(const vec3& position)
{
	m_params.at = position;
	m_is_dirty = true;
}

