#pragma once
#include "system.h"

class Game;
class event_base;

class HealthSystem : public System
{
public:
	HealthSystem(Game& game);

	void update(float dt) override {};
private:
	void on_collision_event(const event_base& event);
};

