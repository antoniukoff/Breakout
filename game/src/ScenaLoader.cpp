#include "ScenaLoader.h"
#include "LevelData.h"
#include "Game.h"
#include <math/Random.h>
#include "ResourceManager.h"

static SceneData data;

void ScenaLoader::load_scene(Game& game, uint32_t level)
{
	data = SceneData();

	ScenaLoader::create_arena(game);
	ScenaLoader::parse_level(game, g_levels);

	game.set_scene_data(data);
}

void ScenaLoader::parse_level(Game& game, const std::vector<std::vector<int>>& level_data)
{
	int level_x = level_data[0].size();
	int level_y = level_data.size();

	float offset_x = brick_scale.x * 2.0f + brick_scale.x * 0.5f;
	float offset_y = brick_scale.y * 2.0f + brick_scale.y * 0.5f;

	float grid_width = level_x * offset_x;
	float arena_start_pos_x = -(grid_width / 2.0f) + (offset_x / 2.0f);
	float arena_start_pos_y = arena_scale.y - (offset_y / 2.0f);

	for (uint32_t y = 0; y < level_y; y++)
	{
		for (uint32_t x = 0; x < level_x; x++)
		{
			int object_type = level_data[y][x];
			if (object_type < 1)
			{
				continue;  // Skip empty spaces
			}
			float position_x = arena_start_pos_x + (offset_x * x);
			float position_y = arena_start_pos_y - (offset_y * y);

			vec3 position = { position_x, position_y, z_depth + 2.0f };

			create_object(game, object_type, position);
		}
	}
}

void ScenaLoader::create_object(Game& game, int object_type, const vec3& position)
{
	ObjectType obj = static_cast<ObjectType>(object_type);
	switch (obj)
	{
	case BALL:
		create_ball(game, position);
		break;
	case PADDLE:
		create_paddle(game, position);
		break;
	case BRICK:
		create_brick(game, position);
		break;
	case SOLID_BRICK:
		create_solid_brick(game, position);
		break;
	default:
		break;
	}
}

void ScenaLoader::create_arena(Game& game)
{
	auto& registry = game.get_registry();
	auto e = registry.create_entity();

	auto back = ResourceManager::get()->get_mesh("cube");
	auto walls = ResourceManager::get()->get_mesh("paddle");
	auto material = ResourceManager::get()->get_material("shiny_material");

	//// Arena 
	vec3 arena_position = vec3{ 0.0f, 0.0f, z_depth };
	registry.add<TransformComponent>(e, arena_position, arena_scale);
	registry.add<RenderComponent>(e, back, material);
	////

	data.target_pos.y = arena_scale.y - 50.0f;
	data.target_pos.z = z_depth;

	//// Horizontal Walls
	vec3 horizontal_wall_position = arena_position+ vec3{ arena_scale.x, 0.0f, 2.0f };
	vec3 horizontal_wall_scale	  = vec3{ 1.0f, arena_scale.y, 1.0f };
	vec2 horizontal_bounds		  = vec2{ 2.0f * horizontal_wall_scale.x, 2.0f * horizontal_wall_scale.y };


	e = registry.create_entity();
	registry.add<TransformComponent>(e, horizontal_wall_position, horizontal_wall_scale);
	registry.add<BoxColliderComponent>(e, horizontal_bounds);
	registry.add<RenderComponent>(e, walls, material);
	registry.add<CameraShakeComponent>(e);

	horizontal_wall_position.x = -horizontal_wall_position.x;

	e = registry.create_entity();
	registry.add<TransformComponent>(e, horizontal_wall_position, horizontal_wall_scale);
	registry.add<BoxColliderComponent>(e, horizontal_bounds);
	registry.add<RenderComponent>(e, walls, material);
	registry.add<CameraShakeComponent>(e);
	////

	//// Vertical Walls
	vec3 vertical_wall_position = arena_position + vec3{ 0.0f, arena_scale.y, 2.0f };
	vec3 vertical_wall_scale	= vec3{ arena_scale.x, 1.0f, 1.0f };
	vec2 vertical_bounds		= vec2{ 2.0f * vertical_wall_scale.x, 2.0f * vertical_wall_scale.y };

	e = registry.create_entity();
	registry.add<TransformComponent>(e, vertical_wall_position, vertical_wall_scale);
	registry.add<BoxColliderComponent>(e, vertical_bounds);
	registry.add<RenderComponent>(e, walls, material);
	registry.add<CameraShakeComponent>(e);

	vertical_wall_position.y = -vertical_wall_position.y;

	e = registry.create_entity();
	registry.add<TransformComponent>(e, vertical_wall_position, vertical_wall_scale);
	registry.add<BoxColliderComponent>(e, vertical_bounds);
	registry.add<RenderComponent>(e, walls, material);
	registry.add<CameraShakeComponent>(e);
	////
}

void ScenaLoader::create_brick(Game& game, vec3 position)
{
	auto paddle = ResourceManager::get()->get_mesh("paddle");
	auto material = ResourceManager::get()->get_material("shiny_material");

	auto& registry = game.get_registry();
	auto e = registry.create_entity();
	registry.add<TransformComponent>(e, position, brick_scale);
	registry.add<RenderComponent>(e, paddle, material);
	registry.add<BoxColliderComponent>(e, vec2{ brick_scale.x * 2.0f, brick_scale.y * 2.0f });
	registry.add<LifeComponent>(e, 1);
}

void ScenaLoader::create_solid_brick(Game& game, vec3 position)
{
	auto paddle = ResourceManager::get()->get_mesh("paddle");
	auto material = ResourceManager::get()->get_material("shiny_material");

	auto& registry = game.get_registry();
	auto e = registry.create_entity();
	registry.add<TransformComponent>(e, position, brick_scale);
	registry.add<RenderComponent>(e, paddle, material);
	registry.add<BoxColliderComponent>(e, vec2{ brick_scale.x * 2.0f, brick_scale.y * 2.0f });
	registry.add<CameraShakeComponent>(e);
}

void ScenaLoader::create_paddle(Game& game, vec3 position)
{
	auto& registry = game.get_registry();

	auto paddle = ResourceManager::get()->get_mesh("paddle");
	auto material = ResourceManager::get()->get_material("shiny_material");

	entity_id paddle_id = registry.create_entity();
	registry.add<TransformComponent>(paddle_id, position, paddle_scale);
	registry.add<InputComponent>(paddle_id);
	registry.add<BoxColliderComponent>(paddle_id, vec2{ 2.0f * paddle_scale.x, 2.0f * paddle_scale.y });
	registry.add<RenderComponent>(paddle_id, paddle, material);

	data.paddle_id = paddle_id;

	data.camera_pos = vec3{ position.x, position.y - 15.0f, 5.0f };
	data.target_pos.x = position.x;
}

void ScenaLoader::create_ball(Game& game, vec3 position)
{
	auto& registry = game.get_registry();

	auto ball = ResourceManager::get()->get_mesh("ball");
	auto material = ResourceManager::get()->get_material("shiny_material");

	auto e = registry.create_entity();
	registry.add<TransformComponent>(e, position);
	float x = Random::get_random_float(-0.45f, 0.45f);
	float y = Random::get_random_float(0.05f, 0.7f);
	vec3 velocity = vec3::normalize({ x, y, 0.0f }) * 0.25f;
	registry.add<RigidBodyComponent>(e, velocity);
	registry.add<CircleColliderComponent>(e, 1.0f);
	registry.add<RenderComponent>(e, ball, material);

	data.active_balls++;
}

