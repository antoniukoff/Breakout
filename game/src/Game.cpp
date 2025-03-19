#include "Game.h"
#include "Renderer.h"
#include "ScenaLoader.h"
#include <CoreEvents.h>
#include <math/Random.h>
#include "ResourceManager.h"
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

	m_dispatcher.subscribe<RestartEvent>(std::bind(&Game::on_restart, this, std::placeholders::_1));
	m_dispatcher.subscribe<BrickDestroyedEvent>(std::bind(&Game::on_brick_destroyed, this, std::placeholders::_1));
	m_dispatcher.subscribe<KeyPressEvent>(std::bind(&Game::on_key_press, this, std::placeholders::_1));
}

void Game::on_update()
{
	input.update();
	movement.update();
	physics.update();
	respawn_system.update();
	camera_system.update();
	particle_system.update();
	m_camera.update();
}

void Game::render(float interval)
{
	render_system.draw(interval);
	particle_system.draw(interval);
}

void Game::on_restart(const Event& event)
{
	m_registry.reset();
	initialize_level(0);
}

void Game::on_brick_destroyed(const Event& event)
{
	m_scene_data.bricks_destroyed++;
	if (m_scene_data.bricks_destroyed >= m_scene_data.difficulty_threashhold[m_scene_data.current_difficulty])
	{
		m_dispatcher.dispatch(DifficultyIncreasedEvent{});
		m_scene_data.current_difficulty++;
	}
}

void Game::on_key_press(const Event& event)
{
	const KeyPressEvent& e = static_cast<const KeyPressEvent&>(event);
	if (e.key == GLFW_KEY_SPACE)
	{
		m_scene_data.state = GameState::IS_ACTIVE;
		start();
	}
	if (e.key == GLFW_KEY_R)
	{
		m_scene_data.state = GameState::GAME_START;
		m_registry.reset();
		initialize_level(0);
	}
}

void Game::initialize_level(uint32_t level)
{
	reset();
	ScenaLoader::load_scene(*this, level);
}

void Game::initialize_subsystems()
{
	particles.initizalize(500, 0.01f, ResourceManager::get()->get_mesh("cube"));
	line.initizalize(500, 0.5f, ResourceManager::get()->get_mesh("ball"), [](Particle& p){});
	trail.initizalize(500, 0.01f, ResourceManager::get()->get_mesh("ball"), [](Particle& p)
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

void Game::reset()
{	
	movement.reset();
	physics.reset();
	respawn_system.reset();
	particle_system.reset();
}

void Game::start()
{
	movement.init(*this);
	physics.init(*this);
	respawn_system.init(*this);
	particle_system.init(*this);
}

void Game::set_scene_data(const SceneData& data)
{
	m_scene_data = data;
}

std::unique_ptr<Application> create_application()
{
	return std::make_unique<Game>();
}