#include "Game.h"
#include "Renderer.h"
#include "ScenaLoader.h"
#include <CoreEvents.h>
#include <math/Random.h>

Game::Game() 
	: Application(800, 600, "Breakout")
	, input(*this)
	, movement(*this)
	, physics(*this)
	, respawn_system(*this)
	, camera_system(*this)
	, particle_system(*this)
	, health_system(*this)

{
	phong = Shader("assets/shaders/phong.glsl");

	vec3 light_position = { 0.0f, 0.0f , 0.0f };
	vec4 light_color = { 1.0f, 1.0f, 1.0f, 1.0f };
	vec4 cube_color = { 0.87f, 0.34f, 0.47f, 1.0f };

	shiny = Material(&phong);
	shiny.set_vec3("light_position", light_position);
	shiny.set_vec4("model_color", cube_color);
	shiny.set_vec4("light_color", light_color);

	cube = Mesh("assets/meshes/cube.obj");
	sphere = Mesh("assets/meshes/sphere.obj");
	paddle = Mesh("assets/meshes/paddle.obj");

	initialize_subsystems();
	initialize_level(0);

	m_dispatcher.subscribe<RestartEvent>(std::bind(&Game::on_restart, this, std::placeholders::_1));
	m_dispatcher.subscribe<BrickDestroyedEvent>(std::bind(&Game::on_brick_destroyed, this, std::placeholders::_1));
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
	Renderer::begin_frame(m_camera);
	m_registry.for_each<TransformComponent, RenderComponent>([&](
		entity_id e_id,
		component_handle<TransformComponent> transform_component,
		component_handle<RenderComponent> render_component)
		{
			auto& material = render_component.material();
			auto& mesh = render_component.mesh();

			auto& position = transform_component.position();
			auto& prev_position = transform_component.prev_position();
			auto& scale = transform_component.scale();
			auto& angle = transform_component.angle();

			/// lerp position between the frames
			vec3 interpolated_position = prev_position * (1.0f - interval) + position * interval;

			mat4 model = mat4::translate(interpolated_position) * mat4::rotate_z(angle) * mat4::scale(scale);

			Renderer::submit(material, mesh, model);
		});

	particle_system.draw(m_camera, interval);
}

void Game::on_restart(const Event& event)
{
	m_registry.reset();
	initialize_level(m_scene_data.current_level);
}

void Game::on_brick_destroyed(const Event& event)
{
	m_scene_data.number_of_bricks = 0;
	if (m_scene_data.number_of_bricks <= 0)
	{
		reset();
		m_registry.reset();
		ScenaLoader::load_scene(*this, m_scene_data.current_level);
	}
}

void Game::initialize_level(uint32_t level)
{
	m_registry.reset();
	ScenaLoader::load_scene(*this, level);
}

void Game::initialize_subsystems()
{
	batch.initizalize(500, 0.01f, &cube);
	m_camera.init_view(m_scene_data.camera_pos, m_scene_data.target_pos, m_scene_data.global_up);
	m_camera.init_projection(m_window->get_aspect_ratio(), 90.0f, 0.1f, 1000.0f);

	camera_system.init(*this);
	particle_system.init(*this);
	health_system.init(*this);
	respawn_system.init(*this);
}

void Game::reset()
{	
	input.reset();
	movement.reset();
	physics.reset();
	respawn_system.reset();
	camera_system.reset();
	particle_system.reset();
}

std::pair<Mesh&, Material&> Game::get_default_mesh_and_material()
{
	return { cube, shiny };
}

std::pair<Mesh&, Material&> Game::get_paddle()
{
	return { paddle, shiny };
}

std::pair<Mesh&, Material&> Game::get_sphere()
{
	return { sphere, shiny };
}

ParticleBatch& Game::get_particle_batch()
{
	return batch;
}

ShakeCamera& Game::get_active_camera()
{
	return m_camera;
}

EventDispatcher& Game::get_dispatcher()
{
	return m_dispatcher;
}

entity_id Game::get_paddle_id()
{
	return m_scene_data.paddle_id;
}

void Game::set_scene_data(const SceneData& data)
{
	m_scene_data = data;
}

std::unique_ptr<Application> create_application()
{
	return std::make_unique<Game>();
}