#pragma once
#include "system.h"

#include <cstdint>
#include <math/vec3.h>

class Game;
class EventBase;
class ShakeCamera;

class CameraSystem : public System
{
public:
	CameraSystem(Game& game);
	void update(float dt) override;
	void reset();
private:
	void update_camera_shake(float dt);
	void smooth_camera_position(float dt);
	void rotate_around_scene(float dt);
	void on_collision(const EventBase& event);
	void on_ball_respawn(const EventBase& event);
private:
	uint32_t entity_processing = -1;
	float rotate_amount = 0.0f;
};

