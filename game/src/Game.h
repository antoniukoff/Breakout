#pragma once

#include <Application.h>

#include <ecs/registry.h> 

#include "ShakeCamera.h"
#include <ParticleBatch.h>

#include "Components.h"
#include "GameEvents.h"

#include "systems/PhysicsSystem.h"
#include "systems/InputSystem.h"
#include "systems/MovementSystem.h"
#include "systems/CameraSystem.h"
#include "systems/ParticleSystem.h"
#include "systems/HealthSystem.h"
#include "systems/RespawnSystem.h"
#include "systems/RenderSystem.h"


enum class GameState
{
	GAME_START = 0,
	IS_ACTIVE,
	GAME_END
};

struct SceneData
{
	uint32_t current_level = 0;
	uint32_t current_difficulty = 0;
	std::vector<std::vector<int> > difficulty_threashhold =
	{
		{ 1, 1 },
		{ 5, 8, 12, 16, 20 },
		{ 5, 8, 12, 16, 20, 25, 30 }
	};
	uint32_t num_bricks;
	uint32_t bricks_destroyed = 0;

	int lives = 5;
	uint32_t paddle_id = 0;
	uint32_t active_ball_id = 0;
	GameState state = GameState::GAME_START;

	/// Used to interpolate to players position at the start 
	vec3 camera_pos;
	vec3 target_pos;
};

using SceneRegistry = registry<TransformComponent,
	BoxColliderComponent,
	CircleColliderComponent,
	RigidBodyComponent,
	InputComponent,
	RenderComponent,
	CameraShakeComponent,
	LifeComponent,
	LaserComponent>;

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
	void set_scene_data(const SceneData& data);

private:
	void on_restart(const Event& event);
	void reset_ball();
	void on_brick_destroyed(const Event& event);
	void on_brick_respawn(const Event& event);
	void on_key_press(const Event& event);

public:

	inline SceneRegistry&   get_registry()				   { return m_registry; }
	inline ShakeCamera&     get_active_camera()			   { return m_camera; }
	inline EventDispatcher& get_dispatcher()			   { return m_dispatcher; }
	inline ParticleBatch&   get_particle_batch()		   { return particles; }
	inline ParticleBatch&   get_trail_batch()			   { return trail; }
	inline ParticleBatch&   get_line_batch()			   { return line; }
	inline const SceneData& get_scene_data() const	       { return m_scene_data; }
	inline const entity_id  get_paddle_id()	const		   { return m_scene_data.paddle_id; }
	inline const int        get_current_threashold() const { return m_scene_data.difficulty_threashhold[m_scene_data.current_level][m_scene_data.current_difficulty]; }
	inline const GameState& get_state() const			   { return m_scene_data.state; }

private:
	SceneRegistry m_registry;
	ShakeCamera m_camera;

	ParticleBatch particles;
	ParticleBatch line;
	ParticleBatch trail;
	SceneData m_scene_data;

	PhysicsSystem physics;
	InputSystem input;
	MovementSystem movement;
	CameraSystem camera_system;
	ParticleSystem particle_system;
	HealthSystem health_system;
	RespawnSystem respawn_system;
	RenderSystem render_system;
};

