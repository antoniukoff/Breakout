#pragma once
#include "Event.h"
#include <string>

class PlayerMovedEvent : public Event
{
public:
	PlayerMovedEvent() = default;
	std::string direction;
};

