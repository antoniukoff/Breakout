#pragma once
#include <utility>
#include "input.h"

class input_handler
{
public:
	input_handler();
public:
	static bool is_key_pressed(key_code key);
	static bool is_mouse_pressed(mouse_button button);

	static std::pair<float, float> get_mouse_pos();
	static std::pair<float, float> get_rel_mouse_pos();

private:
	static int core_to_glfw_keycode(key_code key);
	static int core_to_glfw_mousebutton(mouse_button key);
};

