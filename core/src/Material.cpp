#include "Material.h"
#include "shader.h"

material::material(shader* shader, const std::string& name)
	: shader_handle(shader)
	, name(name)
{}

void material::set_mat(const std::string name, const mat4& mat)
{
	mat4_map[name] = mat;
}

void material::set_texture(const std::string name, const texture& texture)
{
	texture_map[name] = texture;
}

void material::set_scalar(const std::string name, float value)
{
	float_map[name] = value;
}

void material::set_vec3(const std::string name, const vec3& vec3)
{
	vec3_map[name] = vec3;
}

void material::set_vec4(const std::string name, const vec4& vec4)
{
	vec4_map[name] = vec4;
}

void material::bind() const
{
	shader_handle->bind();

	for (auto [name, mat] : mat4_map)
	{
		shader_handle->upload_mat4(name, mat);
	}

	for (auto [name, texture] : texture_map)
	{
		shader_handle->upload_texture(name, texture);
	}

	for (auto [name, value] : float_map)
	{
		shader_handle->upload_float(name, value);
	}

	for (auto [name, vec3] : vec3_map)
	{
		shader_handle->upload_vec3(name, vec3);
	}

	for (auto [name, vec4] : vec4_map)
	{
		shader_handle->upload_vec4(name, vec4);
	}
}
