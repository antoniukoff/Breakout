#include "InputSystem.h"

#include "../Game.h"
#include "../LevelData.h"

#include <Input.h>

InputSystem::InputSystem(Game& game)
{
	init(game);
}

void InputSystem::update()
{
	if (!game_handle)
	{
		return;
	}

	auto& registry = game_handle->get_registry();

	registry.for_each<TransformComponent, InputComponent>([&](
		entity_id e_id,
		component_handle<TransformComponent> transform_component,
		component_handle<InputComponent> input_component)
		{

			auto& position = transform_component.position();
			auto& scale = transform_component.scale();
			auto& prev_position = transform_component.prev_position();
			auto& angle = transform_component.angle();

			prev_position = position;

			if (Input::is_key_pressed(GLFW_KEY_A))
			{
				position += {-0.5, 0.0f, 0.0f};
			}
			if (Input::is_key_pressed(GLFW_KEY_D))
			{
				position += {0.5, 0.0f, 0.0f};
			}
			if (Input::is_key_pressed(GLFW_KEY_E))
			{
				angle -= 1.0f;
			}
			if (Input::is_key_pressed(GLFW_KEY_Q))
			{
				angle += 1.0f;
			}

			angle = std::clamp(angle, -45.0f, 45.0f);
			position.x = std::clamp(position.x, -arena_scale.x + scale.x, arena_scale.x - scale.x);

			vec3 delta_position = position - prev_position;

			if ((position - prev_position).mag() > 0.0f)
			{
				//	game.get_camera().follow(delta_position);
			}
		});
}
