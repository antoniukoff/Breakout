#include <GLFW/glfw3.h>
#include "EventSystem.h"

EventSystem::EventSystem(GLFWwindow* window_handle) : window_handle(window_handle)
{
	glfwSetWindowUserPointer(window_handle, this);
	glfwSetKeyCallback(window_handle, key_callback_func);
	glfwSetMouseButtonCallback(window_handle, mouse_callback_func);
	glfwSetCursorPosCallback(window_handle, mouse_moved_callback_func);
}

void EventSystem::register_key_event(int key, int action, std::function<void(int key, int action, int x, int y)> callback)
{
	m_event_map[EventType::KEY][key][action] = callback;
}

void EventSystem::register_mouse_event(int key, int action, std::function<void(int key, int action, int x, int y)> callback)
{
	m_event_map[EventType::MOUSE][key][action] = callback;
}

void EventSystem::register_mouse_moved_event(int class_typeid, int action, std::function<void(int key, int action, int x, int y)> callback)
{
	m_event_map[EventType::MOUSE_MOVED][class_typeid][action] = callback;
}

std::pair<float, float> EventSystem::get_rel_mouse_pos()
{
	int wx, wy;
	glfwGetWindowSize(window_handle, &wx, &wy);
	int half_wx = wx / 2;
	int half_wy = wy / 2;

	double x, y;
	glfwGetCursorPos(window_handle, &x, &y);
	float rel_x = (x - half_wx) / half_wx;
	float rel_y = (y - half_wy) / half_wy;

	return{ rel_x, rel_y };
}

void EventSystem::key_callback_func(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	EventSystem* system = static_cast<EventSystem*>(glfwGetWindowUserPointer(window));
	for (auto& [k, a] : system->m_event_map[EventType::KEY])
	{
		if (action > a.size() - 1)
		{
			return;
		}

		if (k == key)
		{
			double x, y;
			glfwGetCursorPos(system->window_handle, &x, &y);

			a[action](key, action, x, y);
		}
	}
}

void EventSystem::mouse_callback_func(GLFWwindow* window, int button, int action, int mods)
{
	EventSystem* system = static_cast<EventSystem*>(glfwGetWindowUserPointer(window));
	for (auto& [b, a] : system->m_event_map[EventType::MOUSE])
	{
		if (action > a.size() - 1)
		{
			return;
		}

		if (b == button)
		{
			double x, y;
			glfwGetCursorPos(system->window_handle, &x, &y);

			a[action](button, action, x, y);
		}
	}
}

void EventSystem::mouse_moved_callback_func(GLFWwindow* window, double xpos, double ypos)
{
	EventSystem* system = static_cast<EventSystem*>(glfwGetWindowUserPointer(window));
	for (auto& [k, a] : system->m_event_map[EventType::MOUSE_MOVED])
	{
		double x, y;
		glfwGetCursorPos(system->window_handle, &x, &y);

		a[1](k, 1, x, y);
	}
}
