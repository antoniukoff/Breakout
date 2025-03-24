#pragma once
#include "System.h"

class Game;

class InputSystem : public System
{
public:
	InputSystem(Game& game);

	void update(float dt) override;
private:
	void update_player_movement(float dt);
	void update_camera_movement(float dt);

	void update_initial_movement_dir(float dt);
private:
};

