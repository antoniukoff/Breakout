#pragma once
#include <iostream>
#include <../vendor/glew/include/GL/glew.h>

#include <Application.h>

#include <Shader.h>
#include "ShakeCamera.h"
#include <Input.h>
#include "Material.h"

#include <ParticleBatch.h>
#include <ParticleEngine.h>

#include <ecs/registry.h> 
#include "Components.h"

#include "GameEvents.h"

vec3 camera_pos = { 0.0f, -40.0f, -5.0f };
vec3 target_pos = { 0.0f, 0.0f, -40.0f };
vec3 global_up = { 0.0f, 1.0f, 0.0f };

class Game : public Application
{
private:
	registry<TransformComponent, 
		BoxColliderComponent, 
		CircleColliderComponent,
		RigidBodyComponent,
		InputComponent, 
		RenderComponent,
		CameraShakeComponent> m_registry;

	ShakeCamera m_camera;

	Mesh cube;
	Mesh sphere;
	Mesh paddle;
	Shader phong;
	Shader debug;
	Material shiny;
	ParticleEngine engine;
	ParticleBatch batch;

	uint32_t debug_vao;

	entity_id paddle_id;

public:
	Game();
	void on_update() override;
	void ball_collision();
	void render(float interval) override;
	void shake_camera();
private:
	void initialize_level();
	void create_paddle();
	void draw_debug(Camera& camera);
	void init_debug();
	void create_ball(vec3 position);
	void create_walls();

	void create_boxes();
	void render_colliders();
	void on_player_moved_event(const Event& event);
};

