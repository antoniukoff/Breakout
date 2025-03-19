#include "RenderSystem.h"
#include "../Game.h"
#include <Renderer.h>

RenderSystem::RenderSystem(Game& game)
{
	init(game);
}

void RenderSystem::draw(float interval)
{
	auto& registry = game_handle->get_registry();
	auto& camera = game_handle->get_active_camera();

	Renderer::begin_frame(camera);
	registry.for_each<TransformComponent, RenderComponent>([&](
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
}
