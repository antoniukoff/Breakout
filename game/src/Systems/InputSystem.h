#pragma once
#include "System.h"

class Game;

class InputSystem : public System
{
public:
	InputSystem(Game& game);

	void update() override;
};

