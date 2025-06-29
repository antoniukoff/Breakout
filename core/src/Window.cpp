#include "window.h"
#include "event_dispatcher.h"
#include "core_events.h"
#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

window::window(float width, float height, const std::string& name) 
	: m_width(width)
	, m_height(height)
{
	if (glfwInit() == GLFW_FALSE)
	{
		std::cerr << "Failed to initialize glfw!" << std::endl;
	};

	m_window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
	glViewport(0, 0, width, height);
	glfwSwapInterval(1);

	initialize_context(4, 6, true);

	glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
		{
			event_dispatcher* dispatcher = static_cast<event_dispatcher*>(glfwGetWindowUserPointer(window));
			window_close_evnt event;
			dispatcher->dispatch(event);
		});

	glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			event_dispatcher* dispatcher = static_cast<event_dispatcher*>(glfwGetWindowUserPointer(window));
			key_press_evnt event;
			event.key = key;
			event.action = action;
			dispatcher->dispatch(event);
		});

}

window::~window()
{
	glfwTerminate();
}

void window::set_event_dispatcher(event_dispatcher* dispatcher)
{
	glfwSetWindowUserPointer(m_window, (void*)(dispatcher));
}

void window::initialize_context(int major, int minor, bool use_core)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE - use_core);

	glfwMakeContextCurrent(m_window);

	glewExperimental = use_core;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize glew!" << std::endl;
	}

	std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << std::endl;
}

void window::poll_events()
{
	glfwPollEvents();
}

void window::swap()
{
	glfwSwapBuffers(m_window);
}

float window::get_aspect_ratio() const
{
	return m_width / m_height;
}

GLFWwindow* window::get_handle() const
{
	return m_window;
}

