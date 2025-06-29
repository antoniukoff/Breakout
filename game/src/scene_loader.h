#pragma once
#include <cstdint>
#include <vector>
#include <math/vec3.h>
#include <math/vec2.h>

class Game;

class ScenaLoader
{
public:
	static void load_scene(Game& game, uint32_t level);
	static void create_brick(Game& game, vec3 position);
	static void create_solid_brick(Game& game, vec3 position);
private:
	static void parse_level(Game& game, const std::vector<std::vector<int>>& level_data);
	static void create_object(Game& game, int object_type, const vec3& position);

	static void create_arena(Game& game);
	static void create_paddle(Game& game, vec3 position);
	static void create_ball(Game& game, vec3 position);
};

