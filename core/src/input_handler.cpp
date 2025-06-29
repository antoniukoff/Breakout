#include "input_handler.h"
#include "application_base.h"

#include <GLFW/glfw3.h>

input_handler::input_handler()
{
}

bool input_handler::is_key_pressed(key_code key)
{
	auto window = application_base::get().get_window()->get_handle();

	int glfw_key = core_to_glfw_keycode(key);
	int state = glfwGetKey(window, glfw_key);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool input_handler::is_mouse_pressed(mouse_button button)
{
	auto window = application_base::get().get_window()->get_handle();

	int glfw_button = core_to_glfw_mousebutton(button);
	int state = glfwGetMouseButton(window, glfw_button);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

std::pair<float, float> input_handler::get_mouse_pos()
{
	auto window = application_base::get().get_window()->get_handle();

	double x, y;
	glfwGetCursorPos(window, &x, &y);

	return{ x, y };
}

std::pair<float, float> input_handler::get_rel_mouse_pos()
{
	auto window = application_base::get().get_window()->get_handle();

	int wx, wy;
	glfwGetWindowSize(window, &wx, &wy);
	int half_wx = wx / 2;
	int half_wy = wy / 2;

	double x, y;
	glfwGetCursorPos(window, &x, &y);
	float rel_x = (x - half_wx) / half_wx;
	float rel_y = (y - half_wy) / half_wy;

	return{ rel_x, rel_y };
}

int input_handler::core_to_glfw_keycode(key_code key)
{
	switch (key)
	{
	case key_code::W: return GLFW_KEY_W;
	case key_code::A: return GLFW_KEY_A;
	case key_code::S: return GLFW_KEY_S;
	case key_code::D: return GLFW_KEY_D;
	case key_code::SPACE: return GLFW_KEY_SPACE;
	default: return 0;
	}
}

int input_handler::core_to_glfw_mousebutton(mouse_button button)
{
	switch (button)
	{
	case mouse_button::LEFT: return GLFW_MOUSE_BUTTON_1;
	case mouse_button::RIGHT: return GLFW_MOUSE_BUTTON_2;
	default: return 0;
	}
}

