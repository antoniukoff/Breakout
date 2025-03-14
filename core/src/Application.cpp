#include "Application.h"
#include <GLFW/glfw3.h>

Application* Application::s_instance = nullptr;

Application::Application(int width, int height)
{
	s_instance = this;

	m_window = new Window(width, height, "Breakout");
	m_event_system = new EventSystem(m_window->get_handle());
	m_renderer = new Renderer();
}

Application::~Application()
{
	delete m_window;
	delete m_event_system;
	delete m_renderer;
}

void Application::run()
{
	const double ms_per_update = 1.0 / 60.0;
	double previous = glfwGetTime();
	double lag = 0.0;
	while (true)
	{
		double current = glfwGetTime();
		double elapsed = current - previous;
		previous = current;
		lag += elapsed;

		m_window->poll_events();

		while (lag >= ms_per_update)
		{
			on_update();
			lag -= ms_per_update;
		}

		float interval = lag / ms_per_update;

		render(interval);
		m_window->swap();

	}
}
