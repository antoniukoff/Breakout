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

class OnGameWon : public Event
{
public:
};