#pragma once
#include <camera.h>
class ShakeCamera : public camera
{
public:
	void update(float dt) override;

	void add_yaw(float delta) {
		temp_yaw = delta; m_is_dirty = true;
	}
	void add_pitch(float shake_camera) {
		temp_pitch = shake_camera; m_is_dirty = true;
	}
	void add_roll(float delta) {
		temp_roll = delta; m_is_dirty = true;
	}
private:
	float temp_yaw = 0.0f, temp_pitch = 0.0f, temp_roll = 0.0f;
};

