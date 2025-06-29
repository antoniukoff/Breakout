#pragma once
#include <memory>
#include "core_events.h"

#include "window.h"
#include "event_dispatcher.h"

class ApplicationBase
{
public:
	ApplicationBase(int width, int height, const std::string& app_name);
	virtual ~ApplicationBase() {}

	void run();

	virtual void on_update(float dt) = 0;
	virtual void on_render(float interval) = 0;

	Window* get_window()
	{
		return m_window.get();
	}

	static ApplicationBase& get()
	{
		return *s_instance;
	}
private:
	void on_window_close(const WindowCloseEvent& event);

private:
	bool m_is_running = true;
	static ApplicationBase* s_instance;

protected:
	std::unique_ptr<Window> m_window;
	EventDispatcher m_dispatcher;
};


