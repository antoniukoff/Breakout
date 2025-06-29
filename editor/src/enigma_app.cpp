#include "enigma_app.h"

#include "glew.h"
#include "glfw3.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include <input.h>
#include <renderer.h>
#include <asset_library.h>
#include <math/random.h>

constexpr uint32_t default_width = 1920.0f;
constexpr uint32_t default_height = 1080.0f;


constexpr uint32_t reflecs::g_max_entities = 5;
constexpr uint32_t num_lights = 1;

struct point_light
{
	struct render_data
	{
		mesh* mesh;
		material* material;
	} m_render_data{};

	vec3 position;
	float padding{};
	vec4 color;

	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;

	float padding2{};
};

struct scene_data
{
	mat4 projection_matrix;
	mat4 view_matrix; 

	vec3 camera_world;
	float padding{};

	point_light lights[num_lights];
};

static scene_data scene_data;

editor::editor()
	: application_base(default_width, default_height, "editor")
{
	init_ui();
	init_scene_buffer();

	create_scene_lights();
}

editor::~editor()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void editor::init_ui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(application_base::get().get_window()->get_handle(), true);
	ImGui_ImplOpenGL3_Init();
}

void editor::init_scene_buffer()
{
	glGenBuffers(1, &buffer_id);
	glBindBuffer(GL_UNIFORM_BUFFER, buffer_id);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(scene_data), nullptr, GL_DYNAMIC_DRAW); 
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, buffer_id);
}

void editor::create_scene_lights()
{
	auto& res_manager = asset_library::get();
	auto* material = res_manager.get_material("plain");
	auto* mesh = res_manager.get_mesh("ball");

	for (auto & i : scene_data.lights)
	{
		float x = random::get_random_float(-10.0f, 10.0f);
		float z = random::get_random_float(-10.0f, 10.0f);

		vec3 position = vec3{ x, 5.0f, z };

		point_light light;
		light.m_render_data.material = material;
		light.m_render_data.mesh = mesh;

		light.position = position;
		light.color = vec4{ 1.0f, 1.0f, 1.0f, 1.0f };
		i = light;
	}
}

void editor::on_update(float dt)
{
	m_scene_camera.update(dt);

	scene_data.projection_matrix = m_scene_camera.get_projection_matrix();
	scene_data.view_matrix	= m_scene_camera.get_view_matrix(0.0f);

	scene_data.camera_world = m_scene_camera.get_position();

 	glBindBuffer(GL_UNIFORM_BUFFER, buffer_id);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(scene_data), &scene_data);
}

void editor::on_render(float interval)
{
	m_registry.for_each<cmp_transform, cmp_render>([&](entity_id e, cmp_handle<cmp_transform> t, cmp_handle<cmp_render> r)
		{
			auto* mat = &r.material();
			auto* mesh = r.mesh();

			auto& position = t.position();
			auto& scale = t.scale();
			auto& angle = t.angle();

			mat4 model = mat4::translate(position) * mat4::rotate_y(angle) * mat4::scale(scale);
			renderer::submit(mat, mesh, model);
		});

	for (auto& light : scene_data.lights)
	{
		mat4 model = mat4::translate(light.position);
		renderer::submit(light.m_render_data.material, light.m_render_data.mesh, model);
	}

	renderer::end_frame();

	render_ui();
}

void editor::render_ui()
{
	ui_begin_frame();
	auto [type, id] = render_entity_panel();
	render_component_inspector_panel(type, id);

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void editor::ui_begin_frame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

std::pair<entt_type, uint32_t> editor::render_entity_panel()
{
	ImGui::Begin("entity_panel");

	if (ImGui::Button("Create Entity"))
	{
		auto e = m_registry.create_entity();
		m_registry.add<cmp_tag>(e, std::string("Entity "+std::to_string(e)));

		cmp_transform transform;
		transform.scale = { 1.0f, 1.0f, 1.0f };
		transform.angle = { 0.0f };
		m_registry.add<cmp_transform>(e, transform);

		selected_entity.first = entt_type::Entity;
		selected_entity.second = e;

		ImGui::SetNextItemOpen(true);
	}

	if (ImGui::TreeNode("Entities"))
	{
		m_registry.for_each<cmp_tag>([&](entity_id id, cmp_handle<cmp_tag> tag)
			{
				auto& name = tag.tag();
				if (ImGui::Selectable(name.c_str(), selected_entity.second == id))
				{
					selected_entity.first = entt_type::Entity;
					selected_entity.second = id;
				};
			});
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Lights"))
	{
		for (uint32_t i = 0; i < num_lights; ++i)
		{
			if (ImGui::Selectable(std::string("Light Source(" + std::to_string(i) + ")").c_str(), selected_entity.second == i))
			{
				selected_entity.first = entt_type::Light;
				selected_entity.second = i;
			};
		}
		ImGui::TreePop();
	}
	ImGui::End();

	return selected_entity;
}

void editor::render_component_inspector_panel(entt_type type, uint32_t entity)
{
	ImGui::Begin("Component Inspector");

	if (type == entt_type::Entity && entity != -1)
	{
		if (ImGui::BeginMenu("Add Component"))
		{
			if (!m_registry.has<cmp_render>(entity) && ImGui::MenuItem("Render"))
			{
				auto* default_mesh = asset_library::get().get_mesh("cube");
				const auto& material = asset_library::get().get_material_instance("matte_material");
				m_registry.add<cmp_render>(entity, default_mesh, material);
			}
			ImGui::EndMenu();
		}
		if (m_registry.has<cmp_transform>(entity))
		{
			auto [transform] = m_registry.unpack<cmp_transform>(entity);

			if (ImGui::TreeNode("TransformComponent")) {
				ImGui::DragFloat3("Position", reinterpret_cast<float*>(&transform.position()), 0.1f);
				ImGui::DragFloat("Rotation", reinterpret_cast<float*>(&transform.angle()), 0.1f);
				ImGui::DragFloat3("Scale", reinterpret_cast<float*>(&transform.scale()), 0.1f);
				ImGui::TreePop();
			}
		}

		if (m_registry.has<cmp_render>(entity))
		{
			auto [render_component] = m_registry.unpack<cmp_render>(entity);

			auto& mesh = *render_component.mesh();
			auto& material = render_component.material();

			if (ImGui::TreeNode("Render Component")) 
			{
				for (auto& [name, float_param] : material.get_vec4_uniforms())
				{
					ImGui::DragFloat4(name.c_str(), reinterpret_cast<float*>(&float_param), 0.01f, 0.001f, 1.0f);
				}
				for (auto& [name, float_param] : material.get_float_uniforms())
				{
					ImGui::DragFloat(name.c_str(), reinterpret_cast<float*>(&float_param), 0.001f, 0.001f, 1.0f);
				}

				ImGui::TreePop();
			}
		}
	}
	else if (type == entt_type::Light && entity != -1)
	{
		auto& active_light = scene_data.lights[entity];

		ImGui::DragFloat3("Position", reinterpret_cast<float*>(&active_light.position), 0.1f);
		ImGui::DragFloat4("Color", reinterpret_cast<float*>(&active_light.color), 0.01f, 0.001f, 1.0f);

		ImGui::DragFloat("Constant", reinterpret_cast<float*>(&active_light.constant), 0.001f, 0.001f, 1.0f);
		ImGui::DragFloat("Linear", reinterpret_cast<float*>(&active_light.linear), 0.001f, 0.001f, 1.0f);
		ImGui::DragFloat("Quadratic", reinterpret_cast<float*>(&active_light.quadratic), 0.001f, 0.001f, 1.0f);
	}
}

std::unique_ptr<application_base> create_application()
{
	return std::make_unique<editor>();
}