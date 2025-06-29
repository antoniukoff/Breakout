#include "application_base.h"
#include "renderer.h"
#include "resource_manager.h"

#include <GLFW/glfw3.h>

ApplicationBase* ApplicationBase::s_instance = nullptr;

ApplicationBase::ApplicationBase(int width, int height, const std::string& app_name)
{
	s_instance = this;
	m_window = std::make_unique<Window>(width, height, app_name);
	m_window->set_event_dispatcher(&m_dispatcher);
	m_dispatcher.subscribe<WindowCloseEvent>(std::bind(&ApplicationBase::on_window_close, this, std::placeholders::_1));

	vec3 clear_color = vec3{ 0.1f, 0.15f, 0.15f};

	Renderer::initialize(clear_color);
	ResourceManager::initialize("assets/resources.txt");
}

void ApplicationBase::run()
{
	const float ms_per_update = 1.0f / 144.0f;
	double previous = glfwGetTime();
	double lag = 0.0;
	while (m_is_running)
	{

		double current = glfwGetTime();
		double elapsed = current - previous;
		previous = current;
		lag += elapsed;

		m_window->poll_events();

		while (lag >= ms_per_update)
		{
			on_update(ms_per_update);
			lag -= ms_per_update;
		}
		m_dispatcher.process_events();

		Renderer::prepare_new_frame();
		on_render(lag / ms_per_update);

		m_window->swap();
	}
}

void ApplicationBase::on_window_close(const WindowCloseEvent& event)
{
	m_is_running = false;
}
