#pragma once
#include <string>

struct GLFWwindow;
class event_dispatcher;

class window
{
public:
	window(const window& other) = delete;
	window(window&& other) = delete;
	window operator =(const window& other) = delete;
	window operator =(window&& other) = delete;

	window(float width, float height, const std::string& name);
	~window();

	void set_event_dispatcher(event_dispatcher* dispatcher);
	void initialize_context(int major, int minor, bool use_core);
	void poll_events();
	void swap();

	float get_aspect_ratio() const;
	GLFWwindow* get_handle() const;

private:
	bool m_should_close;
	float m_width;
	float m_height;
	GLFWwindow* m_window = nullptr;
};

