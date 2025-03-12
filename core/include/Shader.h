#pragma once
#include "math/mat4.h"
#include <unordered_map>
#include <string>
#include "Texture.h"

class Shader
{
public:
	Shader(const std::string& file_path);

	void bind();
	void unbind();
	void use_texture(Texture& texture, const std::string& sampler_name);

	void upload_mat4(const std::string& uniform_name, const mat4& value);

	unsigned int get_id() const;
private:

	unsigned int find_available_texture_unit(int texture_type);
	int	get_uniform(const std::string& name);

	void									create_shader(const std::string& file_path);
	std::tuple<std::string, std::string>	parse_shader(const std::string& file_path);
	int										compile_shader(unsigned int type, const std::string& source);


private:
	std::unordered_map<std::string, int> m_uniform_map;
	std::vector<TextureUnit> m_texture_units;
	unsigned int m_id = 0;
};

