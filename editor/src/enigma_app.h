#pragma once

#include <application_base.h>
#include <ecs/reflecs.h>
#include "components.h"

#include <camera.h>

#include <color.h>

enum class entt_type
{
	None, Entity, Light
};


class editor : public application_base
{
public:
	editor();
	~editor();

	void init_ui();
	void init_scene_buffer();

	void on_update(float dt) override;
	void on_render(float interval) override;

	void create_scene_lights();
	void render_ui();

private:
	void ui_begin_frame();
	std::pair<entt_type, uint32_t> render_entity_panel();
	void render_component_inspector_panel(entt_type type, uint32_t entity);

	reflecs::registry<cmp_transform, cmp_render, cmp_tag> m_registry;
	camera m_scene_camera;
	std::pair<entt_type, uint32_t> selected_entity{};


	uint32_t buffer_id{};
};

