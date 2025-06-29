#pragma once
#include "math/vec3.h"
#include "math/mat4.h"
#include "texture.h"
#include <unordered_map>
#include <string>
#include <iostream>

class shader;

class material
{
public:
    material() = default;
	material(shader* shader, const std::string& name);
	~material(){}

    void set_mat(const std::string name, const mat4& mat);
    void set_texture(const std::string name, const texture& texture);
    void set_scalar(const std::string name, float value);
    void set_vec3(const std::string name, const vec3& mat);
    void set_vec4(const std::string name, const vec4& mat);

	std::unordered_map<std::string, float>& get_float_uniforms() { return float_map; }
	std::unordered_map<std::string, vec4>& get_vec4_uniforms() { return vec4_map; }

    void bind() const;

	const std::string& get_name() const { return name; }
	const shader& get_shader_handle() const { return *shader_handle; }

private:
	shader* shader_handle = nullptr;
	std::string name;

	std::unordered_map<std::string, texture> texture_map;
	std::unordered_map<std::string, float> float_map;
	std::unordered_map<std::string, vec3> vec3_map;
	std::unordered_map<std::string, vec4> vec4_map;
	std::unordered_map<std::string, mat4> mat4_map;
};

