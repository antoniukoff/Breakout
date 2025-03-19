#pragma once
class Game;

class System
{
public:
	virtual void update() = 0;

	virtual void init(Game& game)
	{
		game_handle = &game;
	};
	virtual void reset()
	{
		if (game_handle)
		{
			game_handle = nullptr;
		}
	};

protected:
	Game* game_handle = nullptr;
};

