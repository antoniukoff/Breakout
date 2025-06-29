#include "input_handler.h"
#include "application_base.h"

#include <GLFW/glfw3.h>

InputHandler::InputHandler()
{
}

bool InputHandler::is_key_pressed(KeyCode key)
{
	auto window = ApplicationBase::get().get_window()->get_handle();

	int glfw_key = core_to_glfw_keycode(key);
	int state = glfwGetKey(window, glfw_key);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool InputHandler::is_mouse_pressed(MouseButton button)
{
	auto window = ApplicationBase::get().get_window()->get_handle();

	int glfw_button = core_to_glfw_mousebutton(button);
	int state = glfwGetMouseButton(window, glfw_button);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

std::pair<float, float> InputHandler::get_mouse_pos()
{
	auto window = ApplicationBase::get().get_window()->get_handle();

	double x, y;
	glfwGetCursorPos(window, &x, &y);

	return{ x, y };
}

std::pair<float, float> InputHandler::get_rel_mouse_pos()
{
	auto window = ApplicationBase::get().get_window()->get_handle();

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

int InputHandler::core_to_glfw_keycode(KeyCode key)
{
	switch (key)
	{
	case KeyCode::W: return GLFW_KEY_W;
	case KeyCode::A: return GLFW_KEY_A;
	case KeyCode::S: return GLFW_KEY_S;
	case KeyCode::D: return GLFW_KEY_D;
	case KeyCode::SPACE: return GLFW_KEY_SPACE;
	default: return 0;
	}
}

int InputHandler::core_to_glfw_mousebutton(MouseButton button)
{
	switch (button)
	{
	case MouseButton::LEFT: return GLFW_MOUSE_BUTTON_1;
	case MouseButton::RIGHT: return GLFW_MOUSE_BUTTON_2;
	default: return 0;
	}
}

