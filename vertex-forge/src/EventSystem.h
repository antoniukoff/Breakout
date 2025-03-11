#pragma once

#include <functional>
#include <array>

struct GLFWwindow;

class EventSystem
{
private:
	enum class EventType
	{
		KEY = 0,
		MOUSE,
		MOUSE_MOVED
	};

public:
    EventSystem(GLFWwindow* window_handle);

    void register_key_event(int key, int action, std::function<void(int key, int action, int x, int y)> callback);
    void register_mouse_event(int key, int action, std::function<void(int key, int action, int x, int y)> callback);
    void register_mouse_moved_event(int class_typeid, int action, std::function<void(int key, int action, int x, int y)> callback);

    std::pair<float, float> get_rel_mouse_pos();

private:
    static void key_callback_func(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_callback_func(GLFWwindow* window, int button, int action, int mods);
    static void mouse_moved_callback_func(GLFWwindow* window, double xpos, double ypos);

private:
    GLFWwindow* window_handle;
    std::unordered_map<EventType, std::unordered_map<int, std::array<std::function<void(int key, int action, double x, double y)>, 2>>> m_event_map;
};

