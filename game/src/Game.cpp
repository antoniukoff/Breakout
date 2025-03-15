#include "Game.h"
#include "Renderer.h"

Game::Game() 
	: Application(800, 600, "Breakout")
{
	phong = Shader("assets/shaders/phong.glsl");

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

	m_dispatcher.subscribe<PlayerMovedEvent>(std::bind(&Game::on_player_moved_event, this, std::placeholders::_1));
}

void Game::initialize_level()
{
	create_walls();
	create_ball({0.0f, 0.0f, -37.5f});
	create_paddle();
}

void Game::create_paddle()
{
	vec3 paddle_position = vec3{ 0.0f, -20.0f, -37.5f };
	vec3 paddle_scale = vec3{ 3.0f, 1.0f, 1.0f };
	auto e = m_registry.create_entity();
	m_registry.add<TransformComponent>(e, paddle_position, paddle_position, paddle_scale);
	m_registry.add<BoxColliderComponent>(e, vec2{ 10.0f, 5.0f });
	m_registry.add<InputComponent>(e);
	m_registry.add<RenderComponent>(e, &paddle, &shiny);
}

void Game::create_ball(vec3 position)
{
	auto e = m_registry.create_entity();
	m_registry.add<TransformComponent>(e, position, position);
	m_registry.add<CircleColliderComponent>(e, 5.0f);
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
	m_registry.add<TransformComponent>(e1, back_wall_transform, back_wall_transform, back_wall_scale);

	m_registry.add<TransformComponent>(e2, horizontal_wall_position, horizontal_wall_position, horizontal_wall_scale);
	horizontal_wall_position.x = -horizontal_wall_position.x;
	m_registry.add<TransformComponent>(e3, horizontal_wall_position, horizontal_wall_position, horizontal_wall_scale);

	m_registry.add<TransformComponent>(e4, vertical_wall_position, vertical_wall_position, vertical_wall_scale);
	vertical_wall_position.y = -vertical_wall_position.y;
	m_registry.add<TransformComponent>(e5, vertical_wall_position, vertical_wall_position, vertical_wall_scale);

	m_registry.add<RenderComponent>(e1, &cube, &shiny);
	m_registry.add<RenderComponent>(e2, &cube, &shiny);
	m_registry.add<RenderComponent>(e3, &cube, &shiny);
	m_registry.add<RenderComponent>(e4, &cube, &shiny);
	m_registry.add<RenderComponent>(e5, &cube, &shiny);
}

void Game::on_player_moved_event(const Event& event)
{
	auto& move_event = static_cast<const PlayerMovedEvent&>(event);
	std::cout << move_event.direction << std::endl;
}

void Game::on_update() 
{
	//m_camera.update();

	m_registry.for_each<TransformComponent, MovementComponent>([this](
		entity_id e_id,
		component_handle<TransformComponent> transform_component,
		component_handle<MovementComponent> movement_component)
		{
			auto& velocity = movement_component.velocity();
			auto& position = transform_component.position();
			auto& prev_position = transform_component.prev_position();

			prev_position = position;
			position += velocity;
		});

	m_registry.for_each<TransformComponent, InputComponent>([this](
		entity_id e_id,
		component_handle<TransformComponent> transform_component,
		component_handle<InputComponent> input_component)
		{
			auto& position = transform_component.position();
			auto& prev_position = transform_component.prev_position();
			auto& angle = transform_component.angle();

			prev_position = position;

			if (Input::is_key_pressed(GLFW_KEY_A))
			{
				position += {-0.05, 0.0f, 0.0f};
			}
			if (Input::is_key_pressed(GLFW_KEY_D))
			{
				position += {  0.05, 0.0f, 0.0f };

			}
			if (Input::is_key_pressed(GLFW_KEY_W))
			{
				position += {0.0f, 0.05, 0.0f};
			}
			if (Input::is_key_pressed(GLFW_KEY_S))
			{
				position += {0.0f, -0.05, 0.0f};

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
	
	ball_collision();
}
vec2 clamp(vec2 to_clamp, vec2 min, vec2 max)
{
	float x = std::clamp(to_clamp.x, min.x, max.x);
	float y = std::clamp(to_clamp.y, min.y, max.y);

	return { x, y };
}
void Game::ball_collision()
{
	m_registry.for_each<TransformComponent, BoxColliderComponent>([&](
		entity_id e_id,
		component_handle<TransformComponent> paddle_transform,
		component_handle<BoxColliderComponent> box_collider)
		{
			m_registry.for_each<TransformComponent, CircleColliderComponent>([&](
				entity_id e_id,
				component_handle<TransformComponent> circle_transform,
				component_handle<CircleColliderComponent> circle_collider)
				{
					vec3 ball_pos = circle_transform.position();
					float ball_radius = circle_collider.radius();

					vec3 paddle_pos = paddle_transform.position();
					float paddle_angle = paddle_transform.angle();
					vec2 paddle_half_dims = box_collider.half_extents();

					vec3 vector_from_ball_to_padde = ball_pos - paddle_pos;
					mat4::mult_vec_by_mat(mat4::rotate_z(paddle_angle), vector_from_ball_to_padde);
					vec2 vec = { vector_from_ball_to_padde.x, vector_from_ball_to_padde.y };
					vec2 clamped = clamp(vec, -paddle_half_dims, paddle_half_dims);
					vec2 diff = vec - clamped;

					bool collision = diff.mag() < ball_radius;
					if (collision)
					{
						std::cout << "Ball Collided" << std::endl;
					}
					else
					{
						std::cout << "Not Collided" << std::endl;

					}
				});
		});
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

			/// Minimize jiggering between the frames
			vec3 interpolated_position = prev_position * (1.0f - interval) + position * interval;

			mat4 model = mat4::translate(interpolated_position) * mat4::rotate_z(angle) * mat4::scale(scale);

			Renderer::submit(material, mesh, model);
		});
}

std::unique_ptr<Application> create_application()
{
	return std::make_unique<Game>();
}