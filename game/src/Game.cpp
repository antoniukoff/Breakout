#include "Game.h"
#include "ScenaLoader.h"
#include <CoreEvents.h>
#include "ResourceManager.h"
#include <math/Random.h>
#include <../vendor/glfw/include/GLFW/glfw3.h>

Game::Game() 
	: Application(800, 600, "Breakout")
	, input(*this)
	, movement(*this)
	, physics(*this)
	, respawn_system(*this)
	, camera_system(*this)
	, particle_system(*this)
	, health_system(*this)
	, render_system(*this)
{
	ResourceManager::initialize("assets/resources.txt");

	initialize_subsystems();
	initialize_level(0);

	m_dispatcher.subscribe<BallRespawnEvent>(std::bind(&Game::on_ball_respawn, this, std::placeholders::_1));
	m_dispatcher.subscribe<BrickRespawnEvent>(std::bind(&Game::on_brick_respawn, this, std::placeholders::_1));
	m_dispatcher.subscribe<BrickDestroyedEvent>(std::bind(&Game::on_brick_destroyed, this, std::placeholders::_1));
	m_dispatcher.subscribe<KeyPressEvent>(std::bind(&Game::on_key_press, this, std::placeholders::_1));
}

void Game::on_update(float dt)
{
	input.update(dt);
	movement.update(dt);
	physics.update(dt);
	respawn_system.update(dt);
	camera_system.update(dt);
	particle_system.update(dt);
	m_camera.update();
}

void Game::render(float interval)
{
	render_system.draw(interval);
	particle_system.draw(interval);
}

void Game::initialize_subsystems()
{
	particles.initizalize(1500, 1.0f, ResourceManager::get()->get_mesh("cube"));
	line.initizalize(300, 50.0f, ResourceManager::get()->get_mesh("ball"), [](Particle& p, float) {});
	trail.initizalize(1000, 0.5f, ResourceManager::get()->get_mesh("ball"), [](Particle& p, float)
		{
			p.scale *= p.life;
			p.color.a *= p.life;
		});

	/// Default camera properties
	vec3 camera_pos = { -50.0f, -50.0f, 60.0f };
	vec3 target_pos = { 0.0f, 0.0f, 0.0f };
	vec3 global_up = { 0.0f, 1.0f, 0.0f };
	m_camera.init_view(camera_pos, target_pos, global_up);
	m_camera.init_projection(m_window->get_aspect_ratio(), 90.0f, 0.1f, 1000.0f);
}

void Game::initialize_level(uint32_t level)
{
	reset();
	m_registry.reset();
	ScenaLoader::load_scene(*this, level);
	std::cout << "\nStarting Level: " << level + 1 << "\nInitial target: " << get_current_difficulty_target() <<" bricks!\n";
}

void Game::on_ball_respawn(const Event& event)
{
	m_scene_data.lives--;
	if (m_scene_data.lives <= 0)
	{
		initialize_level(0);
	}
	else
	{
		reset_ball();
		m_scene_data.state = GameState::GAME_START;
	}
}

void Game::on_brick_destroyed(const Event& event)
{
	m_scene_data.bricks_destroyed++;
	m_scene_data.num_bricks--;

	size_t current_threshold        = get_current_difficulty_target();
	size_t current_level_thresholds = m_scene_data.difficulty_threashhold[m_scene_data.current_level].size();

	if (m_scene_data.bricks_destroyed >= current_threshold)
	{
		if (m_scene_data.current_difficulty < current_level_thresholds - 1)
		{
			m_dispatcher.dispatch(DifficultyIncreasedEvent{});
			m_scene_data.current_difficulty++;
				
			size_t next_threshold    = get_current_difficulty_target();
			size_t bricks_to_destroy = next_threshold - current_threshold;

			std::cout << "Increased difficulty, destroy: " << bricks_to_destroy << " bricks!\n";
		}
		else
		{
			if (m_scene_data.num_bricks <= 0)
			{
				m_dispatcher.dispatch(GameWonEvent{});
				m_scene_data.state = GameState::GAME_END;

				std::cout << "Level " << m_scene_data.current_level + 1 << " complete. Press Space Bar to continue. Press R to restart." << std::endl;
			}
			else
			{
				m_dispatcher.dispatch(LastDifficulty{});

				std::cout << "Targets complete, destroy remaining bricks: " << m_scene_data.num_bricks << std::endl;
			}
		}
	}
}

void Game::on_brick_respawn(const Event& event)
{
	const BrickRespawnEvent& e = static_cast<const BrickRespawnEvent&>(event);
	ScenaLoader::create_brick(*this, e.position);

	m_scene_data.num_bricks++;
}

void Game::on_key_press(const Event& event)
{
	const KeyPressEvent& e = static_cast<const KeyPressEvent&>(event);
	if (e.key == GLFW_KEY_SPACE && e.action == GLFW_PRESS)
	{
		if (m_scene_data.state == GameState::GAME_START)
		{
			m_scene_data.state = GameState::IS_ACTIVE;
		}
		else if (m_scene_data.state == GameState::GAME_END)
		{
			m_scene_data.current_level++;
			if (m_scene_data.current_level < 3)
			{
				initialize_level(m_scene_data.current_level);
			}
			else
			{
				initialize_level(0);
			}
		}
	}
	if (e.key == GLFW_KEY_R && e.action == GLFW_PRESS)
	{
		initialize_level(0);
	}
}

void Game::reset()
{	
	respawn_system.reset();
	particle_system.reset();
}

void Game::reset_ball()
{
	/// Reset balls position
	auto [ball_rigid_body] = m_registry.unpack<RigidBodyComponent>(m_scene_data.active_ball_id);
	auto [paddle_transform] = m_registry.unpack<TransformComponent>(m_scene_data.paddle_id);

	vec3  ball_position = paddle_transform.position() + vec3{ 0.0f, 10.0f, 0.0 };
	float velocity_mag	= ball_rigid_body.velocity().mag();

	float x = Random::get_random_float(-0.45f, 0.45f);
	float y = Random::get_random_float(0.05f, 0.7f);

	vec3 velocity = vec3::normalize(vec3{ x, y, 0.0f }) * velocity_mag;

	m_registry.add<TransformComponent>(m_scene_data.active_ball_id, ball_position);
	m_registry.add<RigidBodyComponent>(m_scene_data.active_ball_id, velocity);
}

void Game::set_scene_data(const SceneData& data)
{
	m_scene_data = data;
}

std::unique_ptr<Application> create_application()
{
	return std::make_unique<Game>();
}