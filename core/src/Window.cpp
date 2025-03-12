#include "Window.h"

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

Window::Window(float width, float height, const std::string& name) 
	: width(width)
	, height(height)
{
	if (glfwInit() == GLFW_FALSE)
	{
		std::cerr << "Failed to initialize glfw!" << std::endl;
	};

	window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
	glViewport(0, 0, width, height);
	glfwSwapInterval(1);

	initialize_context(3, 3, true);

}

void Window::initialize_context(int major, int minor, bool use_core)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE - use_core);

	glfwMakeContextCurrent(window);

	glewExperimental = use_core;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize glew!" << std::endl;
	}
}

void Window::poll_events()
{
	glfwPollEvents();
}

void Window::swap()
{
	glfwSwapBuffers(window);
}

GLFWwindow* Window::get_handle() const
{
	return window;
}

