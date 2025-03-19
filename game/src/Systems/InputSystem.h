#pragma once
#include "System.h"

class Game;

class InputSystem : public System
{
public:
	InputSystem(Game& game);

	void update() override;
private:
	void update_player_movement();
	void update_camera_movement();

	void update_player_trajectory();
private:
};

