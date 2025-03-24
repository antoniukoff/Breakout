#pragma once
class Game;

class System
{
public:
	virtual void update(float dt) = 0;

	virtual void init(Game& game)
	{
		game_handle = &game;
	};
	

protected:
	Game* game_handle = nullptr;
};

