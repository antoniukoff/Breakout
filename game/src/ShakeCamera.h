#pragma once
#include <Camera.h>
class ShakeCamera : public Camera
{
public:
	void update() override;

	void add_yaw(float delta) {
		temp_yaw = delta; m_is_dirty = true;
	}
	void add_pitch(float delta) {
		temp_pitch = delta; m_is_dirty = true;
	}
	void add_roll(float delta) {
		temp_roll = delta; m_is_dirty = true;
	}
private:
	float temp_yaw = 0.0f, temp_pitch = 0.0f, temp_roll = 0.0f;
};

