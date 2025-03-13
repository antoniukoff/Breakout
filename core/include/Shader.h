#pragma once
#include "math/mat4.h"
#include <unordered_map>
#include <string>
#include "Texture.h"

class Shader
{
public:
	Shader() = default;
	Shader(const std::string& file_path);

	void bind() const;
	void unbind() const;
	void use_texture(Texture& texture, const std::string& sampler_name);

	void upload_mat4(const std::string& uniform_name, const mat4& value) const;
	void upload_vec4(const std::string& uniform_name, const vec4& value) const;
	void upload_vec4(const std::string& uniform_name, const vec3& value) const;
	void upload_vec3(const std::string& uniform_name, const vec3& value) const;

	unsigned int get_id() const;
private:

	unsigned int find_available_texture_unit(int texture_type);
	int	get_uniform(const std::string& name) const;

	void									create_shader(const std::string& file_path);
	std::tuple<std::string, std::string>	parse_shader(const std::string& file_path);
	int										compile_shader(unsigned int type, const std::string& source);


private:
	mutable std::unordered_map<std::string, int> m_uniform_map;
	std::vector<TextureUnit> m_texture_units;
	unsigned int m_id = 0;
};

