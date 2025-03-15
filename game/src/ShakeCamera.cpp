#include "ShakeCamera.h"

void ShakeCamera::update()
{
	vec3 look_dir = m_look_dir;

	float curr_yaw = yaw + temp_yaw;
	float curr_pitch = pitch + temp_pitch;

	mat4 m_yaw = mat4::rotate_y(curr_yaw, true);
	mat4 m_pitch = mat4::rotate_x(curr_pitch, true);
	mat4 m_combined = mat4::mult_mat_by_mat(m_yaw, m_pitch);
	mat4::mult_vec_by_mat(m_combined, look_dir);

	m_target = m_camera_pos + look_dir;
	m_is_dirty = true;
}
