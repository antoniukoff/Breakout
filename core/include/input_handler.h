#pragma once
#include <utility>
#include "input.h"

class InputHandler
{
public:
	InputHandler();
public:
	static bool is_key_pressed(KeyCode key);
	static bool is_mouse_pressed(MouseButton button);

	static std::pair<float, float> get_mouse_pos();
	static std::pair<float, float> get_rel_mouse_pos();

private:
	static int core_to_glfw_keycode(KeyCode key);
	static int core_to_glfw_mousebutton(MouseButton key);
};

