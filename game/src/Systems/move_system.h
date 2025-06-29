#pragma once
#include "system.h"

class Game;
class event_base;

class MovementSystem : public System
{
public:
	MovementSystem(Game& game);

	void update(float dt) override;
private:
	void on_diffuculty_increased_event(const event_base& event);
};

