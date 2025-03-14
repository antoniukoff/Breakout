#include "Input.h"
#include "Application.h"

bool Input::is_key_pressed(int key)
{
	auto window = Application::get().get_window()->get_handle();
	int state = glfwGetKey(window, key);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::is_mouse_pressed(int button)
{
	auto window = Application::get().get_window()->get_handle();
	int state = glfwGetMouseButton(window, button);
	return state == GLFW_PRESS || state == GLFW_RELEASE;
}

std::pair<float, float> Input::get_mouse_pos()
{
	auto window = Application::get().get_window()->get_handle();

	double x, y;
	glfwGetCursorPos(window, &x, &y);

	return{ x, y };
}

std::pair<float, float> Input::get_rel_mouse_pos()
{
	auto window = Application::get().get_window()->get_handle();

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
