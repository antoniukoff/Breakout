#include "enigma_app.h"

#include "glew.h"
#include "glfw3.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include <input.h>
#include <renderer.h>
#include <resource_manager.h>
#include <math/random.h>


constexpr uint32_t default_width = 1920.0f;
constexpr uint32_t default_height = 1080.0f;

constexpr uint32_t num_lights = 1;

struct PointLight
{
	struct RenderData
	{
		Mesh* mesh;
		Material* material;
	} m_render_data{};

	vec3 position;
	float padding{};
	vec4 color;

	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;

	float padding2{};
};

struct SceneData
{
	mat4 projection_matrix;
	mat4 view_matrix; 

	vec3 camera_world;
	float padding{};

	PointLight lights[num_lights];
};

static SceneData scene_data;

Enigma3D::Enigma3D()
	: ApplicationBase(default_width, default_height, "EnigmaApp")
{
	init_ui();
	init_scene_buffer();

	m_dispatcher.subscribe<KeyPressEvent>(std::bind(&Enigma3D::on_key_press, this, std::placeholders::_1));

	create_scene_lights();
	auto e = m_registry.create_entity();

	Sample c;
	c.mat.emplace_back();
	m_registry.add<Sample>(e, c);
}

Enigma3D::~Enigma3D()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Enigma3D::init_ui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(ApplicationBase::get().get_window()->get_handle(), true);
	ImGui_ImplOpenGL3_Init();
}

void Enigma3D::init_scene_buffer()
{

	glGenBuffers(1, &buffer_id);
	glBindBuffer(GL_UNIFORM_BUFFER, buffer_id);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(SceneData), nullptr, GL_DYNAMIC_DRAW); 
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, buffer_id);
}

void Enigma3D::create_scene_lights()
{
	auto& res_manager = ResourceManager::get();
	auto* material = res_manager.get_material("plain");
	auto* mesh = res_manager.get_mesh("ball");

	for (auto & i : scene_data.lights)
	{
		float x = Random::get_random_float(-10.0f, 10.0f);
		float z = Random::get_random_float(-10.0f, 10.0f);

		vec3 position = vec3{ x, 5.0f, z };

		PointLight light;
		light.m_render_data.material = material;
		light.m_render_data.mesh = mesh;

		light.position = position;
		light.color = vec4{ 1.0f, 1.0f, 1.0f, 1.0f };
		i = light;
	}
}

void Enigma3D::create_entity()
{

	auto& res_manager = ResourceManager::get();
	auto material = res_manager.get_material_instance("matte_material");
	auto* mesh = res_manager.get_mesh("cube");

	RenderComponent r{
			.mesh = mesh,
			.material = material
	};

	float x = Random::get_random_float(-50.0f, 50.0f);
	float z = Random::get_random_float(-50.0f, 50.0f);

	vec3 position = vec3{ x, 5.0f, z };

	Transform t{
		.position = position,
		.angle = {0.0f},
		.scale = {2.0f, 2.0f, 2.0f}
	};

	auto e = m_registry.create_entity();
	m_registry.add<RenderComponent>(e, r);
	m_registry.add<Transform>(e, t);
	m_registry.add<TagComponent>(e, "Entity(" + std::to_string(e) + ")");

	entity_count.emplace_back(e);
}

void Enigma3D::on_update(float dt)
{
	m_scene_camera.update(dt);

	scene_data.projection_matrix = m_scene_camera.get_projection_matrix();
	scene_data.view_matrix	= m_scene_camera.get_view_matrix(0.0f);

	scene_data.camera_world = m_scene_camera.get_position();

 	glBindBuffer(GL_UNIFORM_BUFFER, buffer_id);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(SceneData), &scene_data);
}

void Enigma3D::on_render(float interval)
{
	m_registry.for_each<Transform, RenderComponent>([&](entity_id e, component_handle<Transform> t, component_handle<RenderComponent> r)
		{
			auto* mat = &r.material();
			auto* mesh = r.mesh();

			auto& position = t.position();
			auto& scale = t.scale();
			auto& angle = t.angle();

			mat4 model = mat4::translate(position) * mat4::rotate_y(angle) * mat4::scale(scale);
			Renderer::submit(mat, mesh, model);
		});

	for (auto& light : scene_data.lights)
	{
		mat4 model = mat4::translate(light.position);
		Renderer::submit(light.m_render_data.material, light.m_render_data.mesh, model);
	}

	Renderer::end_frame();

	render_ui();
}

void Enigma3D::render_ui()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

#pragma region UIWidgets
	ImGui::Begin("Editor");

	if (ImGui::TreeNode("Entities")) 
	{
		m_registry.for_each<TagComponent>([&](entity_id id, component_handle<TagComponent> tag)
			{
				auto& name = tag.tag();
				if (ImGui::Selectable(name.c_str(), m_selected_entity == id))
				{
					m_entity_type = UISelectable::Entity;
					m_selected_entity = id;
				};
			});
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Lights"))
	{
		for (uint32_t i = 0; i < num_lights; ++i)
		{
			if (ImGui::Selectable(std::string("Light Source(" + std::to_string(i) + ")").c_str(), m_selected_entity == i))
			{
				m_entity_type = UISelectable::Light;
				m_selected_entity = i;
			};
		}
		ImGui::TreePop();
	}
	ImGui::End();

#pragma region ComponentInspector

	ImGui::Begin("Inspector");

	if (m_entity_type == UISelectable::Entity && m_selected_entity != -1)
	{
		if (m_registry.has<Transform>(m_selected_entity))
		{
			auto [transform] = m_registry.unpack<Transform>(m_selected_entity);

			if (ImGui::TreeNode("TransformComponent")) {
				ImGui::DragFloat3("Position", reinterpret_cast<float*>(&transform.position()), 0.1f);
				ImGui::DragFloat("Rotation", reinterpret_cast<float*>(&transform.angle()), 0.1f);
				ImGui::DragFloat3("Scale", reinterpret_cast<float*>(&transform.scale()), 0.1f);
				ImGui::TreePop();
			}
		}

		if (m_registry.has<RenderComponent>(m_selected_entity))
		{
			auto [render_component] = m_registry.unpack<RenderComponent>(m_selected_entity);

			auto& mesh = *render_component.mesh();
			auto& material = render_component.material();

			if (ImGui::TreeNode("Render Component")) {
				if (material.get_shader_handle().get_name() == "phong")
				{
					for (auto& [name, float_param] : material.get_vec4_uniforms())
					{
						ImGui::DragFloat4(name.c_str(), reinterpret_cast<float*>(&float_param), 0.01f, 0.001f, 1.0f);
					}
					for (auto& [name, float_param] : material.get_float_uniforms())
					{
						ImGui::DragFloat(name.c_str(), reinterpret_cast<float*>(&float_param), 0.001f, 0.001f, 1.0f);
					}
				}

				ImGui::TreePop();
			}
		}
	}
	else if (m_entity_type == UISelectable::Light && m_selected_entity != -1)
	{
		auto& active_light = scene_data.lights[m_selected_entity];

		ImGui::DragFloat3("Position", reinterpret_cast<float*>(&active_light.position), 0.1f);
		ImGui::DragFloat4("Color", reinterpret_cast<float*>(&active_light.color), 0.01f, 0.001f, 1.0f);

		ImGui::DragFloat("Constant", reinterpret_cast<float*>(&active_light.constant), 0.001f, 0.001f, 1.0f);
		ImGui::DragFloat("Linear", reinterpret_cast<float*>(&active_light.linear), 0.001f, 0.001f, 1.0f);
		ImGui::DragFloat("Quadratic", reinterpret_cast<float*>(&active_light.quadratic), 0.001f, 0.001f, 1.0f);
	}
	
#pragma endregion

#pragma endregion

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Enigma3D::on_key_press(KeyPressEvent event)
{
	if (event.key == GLFW_KEY_R && event.action == GLFW_PRESS)
	{
		create_entity();
	}
	else if (event.key == GLFW_KEY_T && event.action == GLFW_PRESS)
	{
		uint32_t i = entity_count.back();
		m_registry.destroy(i);
		entity_count.pop_back();
	}
}

std::unique_ptr<ApplicationBase> create_application()
{
	return std::make_unique<Enigma3D>();
}
