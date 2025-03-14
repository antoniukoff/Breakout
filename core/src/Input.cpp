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
