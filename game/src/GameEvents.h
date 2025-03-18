#pragma once
#include "Event.h"
#include <string>
#include <math/vec3.h>

class PlayerMovedEvent : public Event
{
public:
	PlayerMovedEvent() = default;
	std::string direction;
};

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

class NextLevelEvent : public Event
{
public:
	NextLevelEvent() = default;
};


