#pragma once
#include "System.h"

class Game;

class MovementSystem : public System
{
public:
	MovementSystem(Game& game);

	void update() override;
};

