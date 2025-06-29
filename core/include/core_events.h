#pragma once
#include "event_base.h"

class WindowCloseEvent : public EventBase
{
public:
	WindowCloseEvent() = default;
};

class KeyPressEvent : public EventBase
{
public:
	int key;
	int action;
};

class MousePressEvent : public EventBase
{
public:
	int button;
	int action;
	float screen_x, screen_y;
};
