#pragma once
#include "system.h"

class RenderSystem : public System
{
public:
	RenderSystem(Game& game);
	void update(float dt) override {}
	void draw(float interval);
};

