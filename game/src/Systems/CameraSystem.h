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
	void update() override;
private:
	void update_camera_shake();
	void smooth_camera_position();
	void on_collision(const Event& event);
private:
	uint32_t entity_processing = -1;
	vec3 target_position;
};

