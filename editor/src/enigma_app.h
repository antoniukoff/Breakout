#pragma once

#include <application_base.h>
#include <ecs/reflecs.h>
#include "components.h"

#include <camera.h>

#include <color.h>

enum class UISelectable
{
	None, Entity, Light
};


class Enigma3D : public ApplicationBase
{
public:
	Enigma3D();
	~Enigma3D();

	void init_ui();

	void init_scene_buffer();

	void create_scene_lights();

	void create_entity();

	void on_update(float dt) override;
	void on_render(float interval) override;

	void render_ui();

	void on_key_press(KeyPressEvent event);

private:
	reflecs::registry<Sample, Transform, RenderComponent, TagComponent> m_registry;
	Camera m_scene_camera;

	UISelectable m_entity_type;

	uint32_t buffer_id;
	uint32_t m_selected_entity = -1;
	std::vector<uint32_t> entity_count;
};

