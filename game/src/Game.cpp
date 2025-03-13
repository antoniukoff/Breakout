#include <Application.h>
#include <Shader.h>
#include <Window.h>
#include <EventSystem.h>
#include <Camera.h>
#include <CubeTypes.h>
#include <Renderer.h>

vec3 camera_pos = { 0.0f, 0.0f, 0.5f };
vec3 target_pos = { 0.0f, 0.0f, 0.0f };
vec3 global_up = { 0.0f, 1.0f, 0.0f };

class Game : public Application
{
private:
	Window m_window;
	EventSystem m_system;
	Camera m_camera;
	Shader shader;
	Mesh cube;
	Renderer renderer;

public:
	Game()
		: m_window(800, 600, "VertexForge")
		, m_system(m_window.get_handle())
		, shader("assets/shaders/default.glsl")
	{
		m_camera.init_view(camera_pos, target_pos, global_up);
		m_camera.init_projection(m_window.get_aspect_ratio(), 90.0f, 0.1f, 100.0f);

		m_camera.register_key_events(m_system);
		m_camera.register_mouse_events(m_system);

		cube = Mesh("assets/meshes/sphere.obj");
	}
	void run() override
	{
		vec3 light_position = { -5.0f, 0.0f , 0.0f };
		vec3 light_color = { 1.0f, 1.0f, 1.0f };
		vec3 cube_color = { 0.0f, 0.34f, 0.47f };

		shader.bind();
		shader.upload_vec4("model_color", cube_color);
		shader.upload_vec4("light_color", light_color);
		shader.upload_vec3("light_position", light_position);

		while (true)
		{
			m_window.poll_events();
			m_camera.update();

			renderer.begin_frame(m_camera);
			mat4 cube_1 = mat4::translate({ 0.0f, 0.0f, -20.0f });
			mat4 cube_2 = mat4::translate({ -20.0f, 0.0f, -20.0f });
			renderer.submit(shader, cube, { cube_1, cube_2 });
			
			m_window.swap();
		}
	}
};

std::unique_ptr<Application> create_application()
{
	return std::make_unique<Game>();
}