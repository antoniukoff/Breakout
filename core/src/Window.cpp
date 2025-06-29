#include "window.h"
#include "event_dispatcher.h"
#include "core_events.h"
#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

Window::Window(float width, float height, const std::string& name) 
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
			EventDispatcher* dispatcher = static_cast<EventDispatcher*>(glfwGetWindowUserPointer(window));
			WindowCloseEvent event;
			dispatcher->dispatch(event);
		});

	glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			EventDispatcher* dispatcher = static_cast<EventDispatcher*>(glfwGetWindowUserPointer(window));
			KeyPressEvent event;
			event.key = key;
			event.action = action;
			dispatcher->dispatch(event);
		});

}

Window::~Window()
{
	glfwTerminate();
}

void Window::set_event_dispatcher(EventDispatcher* dispatcher)
{
	glfwSetWindowUserPointer(m_window, (void*)(dispatcher));
}

void Window::initialize_context(int major, int minor, bool use_core)
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

void Window::poll_events()
{
	glfwPollEvents();
}

void Window::swap()
{
	glfwSwapBuffers(m_window);
}

float Window::get_aspect_ratio() const
{
	return m_width / m_height;
}

GLFWwindow* Window::get_handle() const
{
	return m_window;
}

