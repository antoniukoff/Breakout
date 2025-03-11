//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <vector>
//
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb/stb_image.h"
//
//#include "math/mat4.h"
//#include "EventSystem.h"
//#include "Camera.h"
//#include "Window.h"
//#include "Shader.h"
//#include "VertexLayout.h"
//#include "CubeTypes.h"
//#include "VertexArray.h"
//#include "VertexBuffer.h"
//
//#define NORMALIZE_COLOR(color) color / 255.0f
//
//unsigned int load_texture(const std::string& file_name)
//{
//    unsigned int texture_id = 0;
//    glGenTextures(1, &texture_id);
//    glBindTexture(GL_TEXTURE_2D, texture_id);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    int width = 0;
//    int height = 0;
//    int n_channels = 0;
//    unsigned char* data = stbi_load(file_name.c_str(), &width, &height, &n_channels, 0);
//    if (!data)
//    {
//        glDeleteTextures(1, &texture_id);
//        return -1;
//    }
//
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, n_channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
//    glGenerateMipmap(GL_TEXTURE_2D);
//
//    glBindTexture(GL_TEXTURE_2D, 0);
//    stbi_image_free(data);
//
//    return texture_id;
//}
//
//
//int main()
//{
//    Window window(800, 600, "VertexForge");
//    window.initialize_context(3, 3, true);
//
//    EventSystem system(window.get_handle());
//
//    Shader shader("assets/shaders/default.glsl");
//    Shader light_shader("assets/shaders/light.glsl");
//
//    vec3 camera_pos = { 0.0f, 0.0f, 0.5f };
//    vec3 target_pos = { 0.0f, 0.0f, 0.0f };
//    vec3 global_up = { 0.0f, 1.0f, 0.0f };
//    Camera camera(camera_pos, target_pos, global_up);
//
//    camera.register_key_events(system);
//    camera.register_mouse_events(system);
//
//	VertexBuffer cube_vbo;
//	VertexArray cube_vao;
//
//    cube_vbo.upload_data(get_textured_cube());
//
//	VertexLayout layout;
//    layout.create_layout({
//        {0, 3, GL_FLOAT, GL_FALSE},
//        {1, 2, GL_FLOAT, GL_FALSE},
//        {2, 1, GL_FLOAT, GL_FALSE}
//        });
//
//	
//	cube_vbo.set_layout(layout);
//	cube_vao.set_vbo(cube_vbo);
//
//	auto texture  = load_texture("assets/textures/wall.jpg");
//	auto texture2 = load_texture("assets/textures/awesomeface.png");
//
//    glEnable(GL_DEPTH_TEST);
//    glClearColor(NORMALIZE_COLOR(124.0f), NORMALIZE_COLOR(163.0f), NORMALIZE_COLOR(64.0f), NORMALIZE_COLOR(255.0f));
//
//    mat4 projection_matrix = mat4::calculate_projection(800.0f / 600.0f, 90.0f, 0.1f, 100.0f);
//
//	const vec3& light_pos = camera.get_position();
//
//    while (true)
//    {
//        window.poll_events();
//        camera.update();
//
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        //std::vector<float> culled_triangles;
//
//        /*for (int i = 0; i < sizeof(vertex_buffer) / (sizeof(float) * 6); i += 3)
//        {
//            int i_offset = i * 6;
//            float x = vertex_buffer[i_offset];
//            float y = vertex_buffer[i_offset + 1];
//            float z = vertex_buffer[i_offset + 2];
//            float s = vertex_buffer[i_offset + 3];
//            float r = vertex_buffer[i_offset + 4];
//            vec3 vertex1 = vec3{ x, y ,z};
//
//            i_offset += 6;
//            float x1 = vertex_buffer[i_offset];
//            float y1 = vertex_buffer[i_offset + 1];
//            float z1 = vertex_buffer[i_offset + 2];
//            float s1 = vertex_buffer[i_offset + 3];
//            float r1 = vertex_buffer[i_offset + 4];
//            vec3 vertex2 = vec3{ x1, y1 ,z1};
//
//            i_offset += 6;
//            float x2 = vertex_buffer[i_offset];
//            float y2 = vertex_buffer[i_offset + 1];
//            float z2 = vertex_buffer[i_offset + 2];
//            float s2 = vertex_buffer[i_offset + 3];
//            float r2 = vertex_buffer[i_offset + 4];
//            vec3 vertex3 = vec3{ x2, y2 ,z2};
//
//            mat4::mult_vec_by_mat(m_model, vertex1);
//            mat4::mult_vec_by_mat(m_model, vertex2);
//            mat4::mult_vec_by_mat(m_model, vertex3);
//
//
//            vec3 transformed_v1 = vec3{ vertex1.x, vertex1.y, vertex1.z };
//            vec3 transformed_v2 = vec3{ vertex2.x, vertex2.y, vertex2.z };
//            vec3 transformed_v3 = vec3{ vertex3.x, vertex3.y, vertex3.z };
//            
//            vec3 v1 = transformed_v1 - transformed_v2;
//            vec3 v2 = transformed_v3 - transformed_v2;
//
//            vec3 normal = vec3::normalize(vec3::cross(v2, v1));
//
//            vec3 vertex_to_camera = vec3::normalize(camera.get_position() - transformed_v2);
//
//            float dot = vec3::dot(normal, vertex_to_camera);
//
//            if (dot > 0.0f)
//            {
//                vec3 light_dir = vec3::normalize(light_pos - cube_pos);
//
//                float light_coeff = vec3::dot(light_dir, normal);
//
//                culled_triangles.push_back(transformed_v1.x);
//                culled_triangles.push_back(transformed_v1.y);
//                culled_triangles.push_back(transformed_v1.z);
//                culled_triangles.push_back(s);
//                culled_triangles.push_back(r);
//                culled_triangles.push_back(light_coeff);
//
//                culled_triangles.push_back(transformed_v2.x);
//                culled_triangles.push_back(transformed_v2.y);
//                culled_triangles.push_back(transformed_v2.z);
//                culled_triangles.push_back(s1);
//                culled_triangles.push_back(r1);
//                culled_triangles.push_back(light_coeff);
//
//
//                culled_triangles.push_back(transformed_v3.x);
//                culled_triangles.push_back(transformed_v3.y);
//                culled_triangles.push_back(transformed_v3.z);
//                culled_triangles.push_back(s2);
//                culled_triangles.push_back(r2);
//                culled_triangles.push_back(light_coeff);
//            }
//        }*/
//	    mat4 m_model = mat4::translate({ 0.0f, 0.0f, -20.0f });
//        {
//            shader.bind();
//
//            glActiveTexture(GL_TEXTURE0);
//            glBindTexture(GL_TEXTURE_2D, texture);
//
//            glActiveTexture(GL_TEXTURE1);
//            glBindTexture(GL_TEXTURE_2D, texture2);
//
//            int sampler_1 = glGetUniformLocation(shader.get_id(), "texture_0");
//            int sampler_2 = glGetUniformLocation(shader.get_id(), "texture_1");
//
//            glUniform1i(sampler_1, 0);
//            glUniform1i(sampler_2, 1);
//
//            shader.upload_mat4("projection", projection_matrix);
//            shader.upload_mat4("view", camera.get_view_matrix());
//            shader.upload_mat4("model", m_model);
//
//            cube_vao.bind();
//            //glBufferSubData(GL_ARRAY_BUFFER, 0, culled_triangles.size() * sizeof(float), culled_triangles.data());
//            glDrawArrays(GL_TRIANGLES, 0, 216 / 6);
//            cube_vao.unbind();
//            shader.unbind();
//        }
//
//        m_model = mat4::translate({ -20.0f, 0.0f, -20.0f });
//		{
//			shader.bind();
//
//			glActiveTexture(GL_TEXTURE0);
//			glBindTexture(GL_TEXTURE_2D, texture);
//
//			glActiveTexture(GL_TEXTURE1);
//			glBindTexture(GL_TEXTURE_2D, texture2);
//
//			int sampler_1 = glGetUniformLocation(shader.get_id(), "texture_0");
//			int sampler_2 = glGetUniformLocation(shader.get_id(), "texture_1");
//
//			glUniform1i(sampler_1, 0);
//			glUniform1i(sampler_2, 1);
//
//			shader.upload_mat4("projection", projection_matrix);
//			shader.upload_mat4("view", camera.get_view_matrix());
//			shader.upload_mat4("model", m_model);
//
//			cube_vao.bind();
//			//glBufferSubData(GL_ARRAY_BUFFER, 0, culled_triangles.size() * sizeof(float), culled_triangles.data());
//			glDrawArrays(GL_TRIANGLES, 0, 216 / 6);
//			cube_vao.unbind();
//			shader.unbind();
//		}
//
//        window.swap();
//    }
//
//   
//    glfwTerminate();
//    return 0;
//}
//
//
