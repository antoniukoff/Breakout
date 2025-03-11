#pragma once
#include <string>

struct GLFWwindow;

class Window
{
public:
	Window(const Window& other) = delete;
	Window(Window&& other) = delete;
	Window operator =(const Window& other) = delete;
	Window operator =(Window&& other) = delete;

	Window(float width, float height, const std::string& name);

	void initialize_context(int major, int minor, bool use_core);
	void poll_events();
	void swap();

	GLFWwindow* get_handle() const;

private:
	float width;
	float height;
	GLFWwindow* window = nullptr;
};

