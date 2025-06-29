#pragma once
#include "system.h"

class Game;
class EventBase;

class HealthSystem : public System
{
public:
	HealthSystem(Game& game);

	void update(float dt) override {};
private:
	void on_collision_event(const EventBase& event);
};

