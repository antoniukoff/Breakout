#pragma once
#include "system.h"

class Game;
class EventBase;

class MovementSystem : public System
{
public:
	MovementSystem(Game& game);

	void update(float dt) override;
private:
	void on_diffuculty_increased_event(const EventBase& event);
};

