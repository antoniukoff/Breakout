#pragma once
#include "math/vec3.h"
#include "math/mat4.h"
#include "texture.h"
#include <unordered_map>
#include <string>
#include <iostream>

class Shader;

class Material
{
public:
    Material() = default;
	Material(Shader* shader, const std::string& name);
	~Material(){}

    void set_mat(const std::string name, const mat4& mat);
    void set_texture(const std::string name, const Texture& texture);
    void set_scalar(const std::string name, float value);
    void set_vec3(const std::string name, const vec3& mat);
    void set_vec4(const std::string name, const vec4& mat);

	std::unordered_map<std::string, float>& get_float_uniforms() { return float_map; }
	std::unordered_map<std::string, vec4>& get_vec4_uniforms() { return vec4_map; }

    void bind() const;

	const std::string& get_name() const { return name; }
	const Shader& get_shader_handle() const { return *shader_handle; }

private:
	Shader* shader_handle = nullptr;
	std::string name;

	std::unordered_map<std::string, Texture> texture_map;
	std::unordered_map<std::string, float> float_map;
	std::unordered_map<std::string, vec3> vec3_map;
	std::unordered_map<std::string, vec4> vec4_map;
	std::unordered_map<std::string, mat4> mat4_map;
};

