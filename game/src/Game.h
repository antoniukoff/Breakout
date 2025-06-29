#pragma once

#include <application_base.h>

#include <ecs/reflecs.h> 

#include "shake_camera.h"
#include <particle_batch.h>

#include "components.h"
#include "game_events.h"

#include "systems/physics_system.h"
#include "systems/input_system.h"
#include "systems/move_system.h"
#include "systems/camera_system.h"
#include "systems/particle_system.h"
#include "systems/health_system.h"
#include "systems/respawn_system.h"
#include "systems/render_system.h"


enum class GameState
{
	GAME_START = 0,
	IS_ACTIVE,
	GAME_END
};

struct scene_data
{
	uint32_t current_level = 0;
	uint32_t current_difficulty = 0;
	std::vector<std::vector<int> > difficulty_threashhold =
	{
		{ 1, 2, 3 },
		{ 3, 5, 8, 12, 15 },
		{  3, 5, 8, 12, 15, 19, 23 }
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

using SceneRegistry = reflecs::registry<TransformComponent,
	BoxColliderComponent,
	CircleColliderComponent,
	RigidBodyComponent,
	BounceComponent,
	cmp_render,
	CameraShakeComponent,
	LifeComponent>;

class Game : public application_base
{
	friend class ScenaLoader;

public:
	Game();
	void on_update(float dt) override;
	void on_render(float interval) override;

private:
	void initialize_level(uint32_t level);
	void initialize_systems();
	void reset();
	void set_scene_data(const scene_data& data);

private:
	void on_ball_respawn(const event_base& event);
	void reset_ball();
	void on_brick_destroyed(const event_base& event);
	void on_brick_respawn(const event_base& event);
	void on_key_press(const event_base& event);

public:

	inline SceneRegistry&   get_registry()						  { return m_registry; }
	inline ShakeCamera&     get_active_camera()					  { return m_camera; }
	inline event_dispatcher& get_dispatcher()					  { return m_dispatcher; }
	inline particle_group&   get_particle_batch()				  { return particles; }
	inline particle_group&   get_trail_batch()					  { return trail; }
	inline particle_group&   get_line_batch()					  { return line; }
	inline scene_data&		get_scene_data()					  { return m_scene_data; }
	inline const entity_id  get_paddle_id()	const				  { return m_scene_data.paddle_id; }
	inline const entity_id  get_ball_id()	const				  { return m_scene_data.active_ball_id; }
	inline const int        get_current_difficulty_target() const { return m_scene_data.difficulty_threashhold[m_scene_data.current_level][m_scene_data.current_difficulty]; }
	inline const int        get_current_level() const			  { return m_scene_data.current_level; }
	inline const int        get_current_difficulty() const		  { return m_scene_data.current_difficulty; }
	inline const int        get_level_diffuculties() const		  { return m_scene_data.difficulty_threashhold[m_scene_data.current_level].size(); }
	inline const GameState& get_state() const					  { return m_scene_data.state; }

private:
	SceneRegistry m_registry;
	ShakeCamera m_camera;

	particle_group particles;
	particle_group line;
	particle_group trail;
	scene_data m_scene_data;

	PhysicsSystem physics;
	InputSystem input;
	MovementSystem movement;
	CameraSystem camera_system;
	ParticleSystem particle_system;
	HealthSystem health_system;
	RespawnSystem respawn_system;
	RenderSystem render_system;
};

