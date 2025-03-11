#include "Shader.h"

#include <gl/glew.h>

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& file_path)
{
	create_shader(file_path);
}

void Shader::bind()
{
	glUseProgram(m_id);
}

void Shader::unbind()
{
	glUseProgram(0);
}

void Shader::upload_mat4(const std::string& uniform_name, const mat4& value)
{
	glUniformMatrix4fv(get_uniform(uniform_name), 1, GL_FALSE, &value(0, 0));
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

	std::cout << ss[0].str() << ss[1].str() << std::endl;

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

