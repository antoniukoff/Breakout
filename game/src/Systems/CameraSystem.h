#pragma once
#include "System.h"

#include <cstdint>
#include <math/vec3.h>

class Game;
class Event;
class ShakeCamera;

class CameraSystem : public System
{
public:
	CameraSystem(Game& game);
	void update(float dt) override;
private:
	void update_camera_shake(float dt);
	void smooth_camera_position(float dt);
	void reset();
	void on_collision(const Event& event);
	void on_ball_respawn(const Event& event);
private:
	uint32_t entity_processing = -1;
};

