#pragma once
#include "Event.h"
#include <string>
#include <math/vec3.h>

class CollisionEvent : public Event
{
public:
	CollisionEvent() = default;
	uint32_t entity_id;
	vec3 position;
};

class BrickDestroyedEvent : public Event
{
public:
	BrickDestroyedEvent() = default;
	vec3 position;
};

class RestartEvent : public Event
{
public:
	RestartEvent() = default;
};

class DifficultyIncreasedEvent : public Event
{
public:
	DifficultyIncreasedEvent() = default;
};

class RespawnEvent : public Event
{
public:
	RespawnEvent() = default;
	vec3 position;
};

class LastDifficulty : public Event
{
public:
	LastDifficulty() = default;
};

class GameWonEvent : public Event
{
public:
	GameWonEvent() = default;
};






