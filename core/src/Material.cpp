#include "Material.h"
#include "Shader.h"

Material::Material(Shader* shader)
	:shader_handle(shader)
{}

void Material::set_mat(const std::string name, const mat4& mat)
{
	mat4_map[name] = mat;
}

void Material::set_texture(const std::string name, const Texture& texture)
{
	texture_map[name] = texture;
}

void Material::set_scalar(const std::string name, float value)
{
	float_map[name] = value;
}

void Material::set_vec3(const std::string name, const vec3& vec3)
{
	vec3_map[name] = vec3;
}

void Material::set_vec4(const std::string name, const vec4& vec4)
{
	vec4_map[name] = vec4;
}

void Material::bind() const
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
