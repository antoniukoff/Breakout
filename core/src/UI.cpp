#include "UI.h"
#include "imgui.h"
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include "Material.h"

void UI::initialize(GLFWwindow* window_handle)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window_handle, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();
}

void UI::being_frame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void UI::end_frame()
{
	// Rendering
// (Your code clears your framebuffer, renders your other stuff etc.)
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	// (Your code calls glfwSwapBuffers() etc.)
}

void UI::present_ui(Light& light_properties, Material& material)
{
	ImGui::Begin("Scene Parameters");

	
	ImGui::Spacing(); // Adds some space before the next section
	ImGui::Text("Cube Material Properties");
	ImGui::Separator();
	ImGui::ColorEdit3("Material Ambient", (float*)&material.ambient);
	ImGui::ColorEdit3("Material Diffuse", (float*)&material.diffuse);
	ImGui::ColorEdit3("Material Specular", (float*)&material.specular);
	ImGui::SliderFloat("Material Shininess", &material.shininess, 1.0f, 500.0f);

	ImGui::End();

}

UI::~UI()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

UI UI::ui_layer;

