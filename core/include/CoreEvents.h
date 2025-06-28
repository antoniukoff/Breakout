#pragma once
#include "Event.h"

class WindowCloseEvent : public Event
{
public:
	WindowCloseEvent() = default;
};

class KeyPressEvent : public Event
{
public:
	int key;
	int action;
};

class MousePressEvent : public Event
{
public:
	int button;
	int action;
	float screen_x, screen_y;
};
