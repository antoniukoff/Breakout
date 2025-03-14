#pragma once
#include "math/vec3.h"
#include "math/mat4.h"
#include "Texture.h"
#include <unordered_map>
#include <string>

class Shader;

class Material
{
public:
    Material() = default;
	Material(Shader* shader);

    void set_mat(const std::string name, const mat4& mat);
    void set_texture(const std::string name, const Texture& texture);
    void set_scalar(const std::string name, float value);
    void set_vec3(const std::string name, const vec3& mat);
    void set_vec4(const std::string name, const vec4& mat);

    void bind() const;

private:
	Shader* shader_handle = nullptr;
	std::unordered_map<std::string, Texture> texture_map;
	std::unordered_map<std::string, float> float_map;
	std::unordered_map<std::string, vec3> vec3_map;
	std::unordered_map<std::string, vec4> vec4_map;
	std::unordered_map<std::string, mat4> mat4_map;
};

