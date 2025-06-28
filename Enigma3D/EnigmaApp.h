#pragma once

#include <Application.h>
#include <ecs/reflecs.h>
#include <Camera.h>

#include "Components.h"
#include "../core/vendor/glew/include/GL/glew.h"

#include <Color.h>

enum class UISelectable
{
	None, Entity, Light
};


class Enigma3D : public Application
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
	registry<Sample, Transform, RenderComponent, TagComponent> m_registry;
	Camera m_scene_camera;

	UISelectable m_entity_type;
	uint32_t m_selected_entity = -1;
	GLuint buffer_id;
	std::queue<int> entity_count;
};

