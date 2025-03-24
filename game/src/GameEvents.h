#pragma once
#include "Event.h"
#include <string>
#include <math/vec3.h>

class CollisionEvent : public Event
{
public:
	uint32_t entity_id;
	vec3 position;
};

class BrickDestroyedEvent : public Event
{
public:
	vec3 position;
};

class GameStarted : public Event
{};

class BallRespawnEvent : public Event
{};

class DifficultyIncreasedEvent : public Event
{};

class BrickRespawnEvent : public Event
{
public:
	vec3 position;
};

class LastDifficulty : public Event
{};

class GameWonEvent : public Event
{};






