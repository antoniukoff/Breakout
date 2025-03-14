#pragma once
#include <../vendor/glfw/include/GLFW/glfw3.h>
#include <utility>

class Input
{
public:
	static bool is_key_pressed(int key);
	static bool is_mouse_pressed(int button);

	std::pair<float, float> get_mouse_pos();

	std::pair<float, float> get_rel_mouse_pos();

};

