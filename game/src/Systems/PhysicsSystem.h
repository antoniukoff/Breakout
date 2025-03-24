#pragma once
#include "System.h"

#include <math/vec2.h>
#include <math/vec3.h>


struct CollisionData
{
	bool collided;
	vec2 collision_vector;
	vec3 closest_point;
};

class Game;
class Event;

class PhysicsSystem : public System
{
public:
	PhysicsSystem(Game& game);

	void update(float dt) override;
private:
	void check_player_level_bounds();
	void update_ball_box_collision();
private:
	CollisionData check_OBB_Circle_collision(const vec3& ball_pos, 
		float radius,
		const vec3& box_pos,
		const vec2& collider_half_dims,
		float box_angle);

	vec3 calculate_paddle_lowest_point(const vec3& paddle_pos, const vec3& collider_collision_point, const vec3& box_extents, float paddle_angle);
	vec3 calculate_best_normal(vec2 distance_vec);

};

