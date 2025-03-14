#pragma once
#include <iostream>

#include <Application.h>

#include <Shader.h>
#include <Camera.h>
#include <Cube.h>
#include <registry.h>
#include "Components.h"
#include <Input.h>
#include "Material.h"

vec3 camera_pos = { 0.0f, -25.0f, -5.0f };
vec3 target_pos = { 0.0f, -2.0f, -40.0f };
vec3 global_up = { 0.0f, 1.0f, 0.0f };

class Game : public Application
{
private:
	registry<TransformComponent, MovementComponent, InputComponent, RenderComponent> m_registry;
	Camera m_camera;

	Mesh cube;
	Mesh sphere;
	Mesh paddle;
	Shader phong;
	Material shiny;

public:
	Game();
	void on_update() override;
	void render(float interval) override;
private:
	void initialize_level();
	void create_paddle();
	void create_ball(vec3 position);
	void create_walls();
};

