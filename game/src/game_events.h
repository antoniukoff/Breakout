#pragma once
#include "event_base.h"
#include <string>
#include <math/vec3.h>

class CollisionEvent : public event_base
{
public:
	uint32_t entity_id;
	vec3 position;
};

class BrickDestroyedEvent : public event_base
{
public:
	vec3 position;
};

class GameStarted : public event_base
{};

class BallRespawnEvent : public event_base
{};

class DifficultyIncreasedEvent : public event_base
{};

class BrickRespawnEvent : public event_base
{
public:
	vec3 position;
};

class GameWonEvent : public event_base
{};






