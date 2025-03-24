#pragma once
#include <memory>

#include "Window.h"
#include "EventDispatcher.h"

class Application
{
public:
	Application(int width, int height, const std::string& app_name);
	~Application() {};

	void run();

	virtual void on_update(float dt) = 0;
	virtual void render(float interval) = 0;

	Window* get_window()
	{
		return m_window.get();
	}

	static Application& get()
	{
		return *s_instance;
	}
private:
	void on_window_close(const Event& event);

private:
	bool m_is_running = true;
	static Application* s_instance;

protected:
	std::unique_ptr<Window> m_window;
	EventDispatcher m_dispatcher;
};


