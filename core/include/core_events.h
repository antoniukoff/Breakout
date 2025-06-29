#pragma once
#include "event_base.h"

class window_close_evnt : public event_base
{
};

class key_press_evnt : public event_base
{
public:
	int key;
	int action;
};

class mouse_press_evnt : public event_base
{
public:
	int button;
	int action;
	float screen_x, screen_y;
};
