#pragma once

#include <Application.h>

#include <Shader.h>
#include <Material.h>
#include <ParticleBatch.h>
#include <ecs/registry.h> 

#include "ShakeCamera.h"

#include "Components.h"
#include "GameEvents.h"

#include "systems/PhysicsSystem.h"
#include "systems/InputSystem.h"
#include "systems/MovementSystem.h"
#include "systems/CameraSystem.h"
#include "systems/ParticleSystem.h"
#include "systems/HealthSystem.h"
#include "systems/RespawnSystem.h"

enum class GameState
{
	GAME_START,
	IS_ACTIVE,
	GAME_END
};

class Game : public Application
{
	friend class ScenaLoader;
public:

	Game();
	void on_update() override;
	void render(float interval) override;

private:
	void initialize_level(uint32_t level);
	void initialize_subsystems();
	void reset();
	void on_restart(const Event& event);
	void on_brick_destroyed(const Event& event);

private:
	registry<TransformComponent,
		BoxColliderComponent,
		CircleColliderComponent,
		RigidBodyComponent,
		InputComponent,
		RenderComponent,
		CameraShakeComponent,
		LifeComponent,
		LaserComponent> m_registry;

	ShakeCamera m_camera;

	Mesh cube;
	Mesh sphere;
	Mesh paddle;

	Shader phong;
	Material shiny;

	ParticleBatch batch;

	PhysicsSystem physics;
	InputSystem input;
	MovementSystem  movement;
	CameraSystem camera_system;
	ParticleSystem particle_system;
	HealthSystem health_system;
	RespawnSystem respawn_system;

public:
	struct SceneData
	{
		uint32_t current_level;
		uint32_t max_velocity_boosts;
		entity_id paddle_id;
		int number_of_balls;
		int number_of_bricks;

		/// default camera properties
		vec3 camera_pos = { -50.0f, -50.0f, 60.0f };
		vec3 target_pos = { 0.0f, 0.0f, 0.0f };
		vec3 global_up = { 0.0f, 1.0f, 0.0f };
	};

private:
	SceneData m_scene_data;

	void set_scene_data(const SceneData& data);
public:
	const SceneData& get_scene_data() const
	{
		return m_scene_data;
	}

	inline auto& get_registry()
	{
		return m_registry;
	};

	ShakeCamera& get_active_camera();
	EventDispatcher& get_dispatcher();

	entity_id get_paddle_id();
	std::pair<Mesh&, Material&> get_default_mesh_and_material();
	std::pair<Mesh&, Material&> get_paddle();
	std::pair<Mesh&, Material&> get_sphere();
	ParticleBatch& get_particle_batch();
};

