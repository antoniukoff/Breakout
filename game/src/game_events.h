#pragma once
#include "event_base.h"
#include <string>
#include <math/vec3.h>

class CollisionEvent : public EventBase
{
public:
	uint32_t entity_id;
	vec3 position;
};

class BrickDestroyedEvent : public EventBase
{
public:
	vec3 position;
};

class GameStarted : public EventBase
{};

class BallRespawnEvent : public EventBase
{};

class DifficultyIncreasedEvent : public EventBase
{};

class BrickRespawnEvent : public EventBase
{
public:
	vec3 position;
};

class GameWonEvent : public EventBase
{};






