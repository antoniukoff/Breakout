#pragma once
#include "math/vec3.h"

struct GLFWwindow;
struct Light;
struct Material;

class UI
{
public:
	static void initialize(GLFWwindow* window_handle);
	static void being_frame();
	static void end_frame();

	static void present_ui(Light& light_properties, Material& material);
private:
	UI() = default;
	~UI();
	static UI ui_layer;
};

