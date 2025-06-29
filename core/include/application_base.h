#pragma once
#include <memory>
#include "core_events.h"

#include "window.h"
#include "event_dispatcher.h"

class application_base
{
public:
	application_base(int width, int height, const std::string& app_name);
	virtual ~application_base() {}

	void run();

	virtual void on_update(float dt) = 0;
	virtual void on_render(float interval) = 0;

	window* get_window()
	{
		return m_window.get();
	}

	static application_base& get()
	{
		return *s_instance;
	}
private:
	void on_window_close(const window_close_evnt& event);

private:
	bool m_is_running = true;
	static application_base* s_instance;

protected:
	std::unique_ptr<window> m_window;
	event_dispatcher m_dispatcher;
};


