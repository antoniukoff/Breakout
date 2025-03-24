#pragma once
#include "System.h"

class Game;
class Event;

class MovementSystem : public System
{
public:
	MovementSystem(Game& game);

	void update(float dt) override;
private:
	void on_diffuculty_increased_event(const Event& event);
};

