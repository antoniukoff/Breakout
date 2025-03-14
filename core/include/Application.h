#pragma once
#include <memory>
#include "Window.h"
#include "EventSystem.h"
#include "Renderer.h"

class Application
{
private:
	static Application* s_instance;
protected:
	Window* m_window;
	EventSystem* m_event_system;
	Renderer* m_renderer;
public:
	Application(int width, int height);
	~Application();

	void run();

	virtual void on_update() = 0;
	virtual void render(float interval) = 0;

	Window* get_window()
	{
		return m_window;
	}

	static Application& get()
	{
		return *s_instance;
	}
};


