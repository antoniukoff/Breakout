#pragma once
#include <iostream>
#include <../vendor/glew/include/GL/glew.h>

#include <Application.h>

#include <Shader.h>
#include <Camera.h>
#include <Cube.h>
#include <Input.h>
#include "Material.h"

#include <ecs/registry.h> 
#include "Components.h"

#include "GameEvents.h"

vec3 camera_pos = { 0.0f, 0.0f, 0.5f };
vec3 target_pos = { 0.0f, 0.0f, 0.0f };
vec3 global_up = { 0.0f, 1.0f, 0.0f };

class Game : public Application
{
private:
	registry<TransformComponent, 
		BoxColliderComponent, 
		CircleColliderComponent,
		MovementComponent,
		InputComponent, 
		RenderComponent> m_registry;

	Camera m_camera;

	Mesh cube;
	Mesh sphere;
	Mesh paddle;
	Shader phong;
	Shader debug;
	Material shiny;

	uint32_t debug_vao;

public:
	Game();
	void on_update() override;
	void ball_collision();
	void render(float interval) override;
private:
	void initialize_level();
	void create_paddle();
	void draw_debug(Camera& camera);
	void init_debug();
	void create_ball(vec3 position);
	void create_walls();

	void render_colliders();
	void on_player_moved_event(const Event& event);
};

