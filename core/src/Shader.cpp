#include "Shader.h"
#include "GLUtils.h"

#include <gl/glew.h>

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& file_path)
{
	create_shader(file_path);

	int max_texture_units;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_texture_units);
	
}

void Shader::bind() const
{
	glUseProgram(m_id);
}

void Shader::unbind() const
{
	glUseProgram(0);
}

void Shader::upload_mat4(const std::string& uniform_name, const mat4& value) 
{
	glUniformMatrix4fv(get_uniform(uniform_name), 1, GL_FALSE, &value(0, 0));
}

void Shader::upload_vec4(const std::string& uniform_name, const vec4& value) 
{
	glUniform4fv(get_uniform(uniform_name), 1, &value.x);
}

void Shader::upload_vec4(const std::string& uniform_name, const vec3& value) 
{
	vec4 v = value.to_vec4();
	glUniform4fv(get_uniform(uniform_name), 1, &v.x);
}

void Shader::upload_vec3(const std::string& uniform_name, const vec3& value) 
{
	glUniform3fv(get_uniform(uniform_name), 1, &value.x);
}

void Shader::upload_float(const std::string& uniform_name, float value)
{
	glUniform1f(get_uniform(uniform_name), value);
}

unsigned int Shader::get_id() const
{
	return m_id;
}

int Shader::get_uniform(const std::string& name) 
{
	if (m_uniform_map.contains(name))
	{
		return m_uniform_map.at(name);
	}

	int u_id = glGetUniformLocation(m_id, name.c_str());
	if (u_id == -1)
	{
		std::cout << " Uniform " << name << " not found" << std::endl;
		return -1;
	}
	m_uniform_map[name] = u_id;
	return u_id;
}

void Shader::create_shader(const std::string& file_path)
{
	auto [vertex, fragment] = parse_shader(file_path);
	unsigned int program = glCreateProgram();
	unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex);
	unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	m_id = program;
}

std::tuple<std::string, std::string> Shader::parse_shader(const std::string& file_path)
{
	std::ifstream file(file_path);

	if (!file.is_open())
	{
		std::cout << "Failed to open resource file: " << file_path << std::endl;
		return {};
	}

	std::string line;
	std::stringstream ss[2];

	enum shader_type
	{
		none = -1,
		vertex,
		fragment
	};

	shader_type type = none;

	while (std::getline(file, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = vertex;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = fragment;
			}
			continue;
		}
		ss[(int)type] << line << std::endl;
	}

	file.close();

	return { ss[0].str(), ss[1].str() };
}

int Shader::compile_shader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex " : "fragment ") << "shader: " << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

void Shader::upload_texture(const std::string& sampler_name, Texture& texture)
{
	/*auto texture_id   = texture.get_id();
	auto texture_type = texture.get_type();

	int sampler_id = get_uniform(sampler_name);

	/// Check if the texture is bound to the unit
	auto it = std::find_if(m_texture_units.begin(), m_texture_units.end(), [&](const TextureUnit& unit)
		{
			return unit.has_bound_texture(texture_type, texture_id);
		});

	if (it != m_texture_units.end())
	{
		return;
	}
	
	/// Find available unit
	unsigned int unit_index = find_available_texture_unit(texture_type);

	m_texture_units[unit_index].assign_texture(texture_type, texture_id);

	glActiveTexture(GL_TEXTURE0 + unit_index);
	glBindTexture(texture_type, texture_id);

	glUniform1i(sampler_id, unit_index);*/
}

unsigned int Shader::find_available_texture_unit(int texture_type)
{
	/*for (int i = 0; i < m_texture_units.size(); ++i)
	{
		auto& current_unit = m_texture_units[i];
		if (current_unit.has_bound_texture(texture_type, EMPTY_TEXTURE_ID))
		{
			return i;
		}
	}*/
	return -1; /// Texture unit overflow
}

