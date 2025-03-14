#pragma once
#include <../vendor/glfw/include/GLFW/glfw3.h>

class Input
{
public:
	static bool is_key_pressed(int key);
	static bool is_mouse_pressed(int button);
};

