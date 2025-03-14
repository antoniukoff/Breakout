#include "Game.h"

Game::Game() 
	: Application(800, 600)
{
	phong = Shader("assets/shaders/default.glsl");

	vec3 light_position = { 0.0f, 0.0f , 0.0f };
	vec4 light_color = { 1.0f, 1.0f, 1.0f, 1.0f };
	vec4 cube_color = { 0.87f, 0.34f, 0.47f, 1.0f };

	shiny = Material(&phong);
	shiny.set_vec3("light_position", light_position);
	shiny.set_vec4("model_color", cube_color);
	shiny.set_vec4("light_color", light_color);

	cube = Mesh(get_cube());
	sphere = Mesh("assets/meshes/sphere.obj");
	paddle = Mesh("assets/meshes/paddle.obj");

	m_camera.init_view(camera_pos, target_pos, global_up);
	m_camera.init_projection(m_window->get_aspect_ratio(), 90.0f, 0.1f, 100.0f);

	initialize_level();
}

void Game::initialize_level()
{
	create_walls();
	//create_ball();
	create_paddle();
}

void Game::create_paddle()
{
	vec3 paddle_position = vec3{ 0.0f, -20.0f, -37.5f };
	vec3 paddle_scale = vec3{ 3.0f, 1.0f, 1.0f };
	auto e = m_registry.create_entity();
	m_registry.add<TransformComponent>(e, paddle_position, paddle_scale);
	m_registry.add<InputComponent>(e);
	m_registry.add<RenderComponent>(e, &paddle, &shiny);
}

void Game::create_ball(vec3 position)
{
	auto e = m_registry.create_entity();
	m_registry.add<TransformComponent>(e, position);
	m_registry.add<RenderComponent>(e, &sphere, &shiny);
}

void Game::create_walls()
{
	vec3 back_wall_transform = vec3{ 0.0f, 0.0f, -40.0f };
	vec3 back_wall_scale = vec3{ 7.5f, 10.0f, 0.5f };

	vec3 horizontal_wall_position = back_wall_transform + vec3{ -22.0f , 0.0f, 2.0f };
	vec3 horizontal_wall_scale = vec3{ 0.5f, 10.0f, 1.5f };

	vec3 vertical_wall_position = back_wall_transform + vec3{ 0.0f, 28.5f, 2.0f };
	vec3 vertical_wall_scale = vec3{ 7.0f, 0.5f, 1.5f };

	auto e1 = m_registry.create_entity();
	auto e2 = m_registry.create_entity();
	auto e3 = m_registry.create_entity();
	auto e4 = m_registry.create_entity();
	auto e5 = m_registry.create_entity();
	m_registry.add<TransformComponent>(e1, back_wall_transform, back_wall_scale);

	m_registry.add<TransformComponent>(e2, horizontal_wall_position, horizontal_wall_scale);
	horizontal_wall_position.x = -horizontal_wall_position.x;
	m_registry.add<TransformComponent>(e3, horizontal_wall_position, horizontal_wall_scale);

	m_registry.add<TransformComponent>(e4, vertical_wall_position, vertical_wall_scale);
	vertical_wall_position.y = -vertical_wall_position.y;
	m_registry.add<TransformComponent>(e5, vertical_wall_position, vertical_wall_scale);

	m_registry.add<RenderComponent>(e1, &cube, &shiny);
	m_registry.add<RenderComponent>(e2, &cube, &shiny);
	m_registry.add<RenderComponent>(e3, &cube, &shiny);
	m_registry.add<RenderComponent>(e4, &cube, &shiny);
	m_registry.add<RenderComponent>(e5, &cube, &shiny);
}

void Game::on_update() 
{
	m_camera.update();

	m_registry.for_each<TransformComponent, MovementComponent>([this](
		entity_id e_id,
		component_handle<TransformComponent> transform_component,
		component_handle<MovementComponent> movement_component)
		{
			auto& velocity = movement_component.velocity();
			auto& position = transform_component.position();

			position += velocity;
		});

	m_registry.for_each<TransformComponent, InputComponent>([this](
		entity_id e_id,
		component_handle<TransformComponent> transform_component,
		component_handle<InputComponent> input_component)
		{
			auto& position = transform_component.position();
			auto& angle = transform_component.angle();

			if (Input::is_key_pressed(GLFW_KEY_A))
			{
				position += {-0.05, 0.0f, 0.0f};
			}
			if (Input::is_key_pressed(GLFW_KEY_D))
			{
				position += {  0.05, 0.0f, 0.0f };
			}
			if (Input::is_key_pressed(GLFW_KEY_E))
			{
				angle -= 1.0f;
			}
			if (Input::is_key_pressed(GLFW_KEY_Q))
			{
				angle += 1.0f;
			}

		});
}

void Game::render(float interval)
{
	m_renderer->begin_frame(m_camera);
	m_registry.for_each<TransformComponent, RenderComponent>([this](
		entity_id e_id,
		component_handle<TransformComponent> transform_component,
		component_handle<RenderComponent> render_component)
		{
			auto& material = render_component.material();
			auto& mesh = render_component.mesh();

			auto& position = transform_component.position();
			auto& scale = transform_component.scale();
			auto& angle = transform_component.angle();

			mat4 model = mat4::translate(position) * mat4::rotate_z(angle) * mat4::scale(scale);

			m_renderer->submit(material, mesh, model);
		});
}

std::unique_ptr<Application> create_application()
{
	return std::make_unique<Game>();
}