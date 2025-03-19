#include "ResourceManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::unique_ptr<ResourceManager> ResourceManager::s_instance = nullptr;

void ResourceManager::initialize(const std::string file_path)
{
	if (s_instance)
	{
		s_instance->meshes.clear();
		s_instance->shaders.clear();
		s_instance->materials.clear();
		s_instance->textures.clear();
	}

	s_instance = std::make_unique<ResourceManager>();

	std::ifstream file(file_path);
	if (!file.is_open())
	{
		std::cout << "Could not open - " << file_path << " - while initializing Resource Manager" << std::endl;
	}

	std::string line;

	while (std::getline(file, line))
	{
		std::istringstream stream(line);
		std::string token;

		stream >> token;

		if (token == "Mesh")
		{
			std::string name;
			std::string path;

			stream >> name >> path;

			s_instance->load_mesh(name, path);
		}
		if (token == "Shader")
		{
			std::string name;
			std::string path;

			stream >> name >> path;

			s_instance->load_shader(name, path);
		}
		if (token == "Material")
		{
			std::string name;
			std::string shader;

			stream >> name >> shader;
			Material* material = s_instance->load_material(name, shader);
			
			std::string type;
			while (stream >> type)
			{
				std::string uniform_name;
				stream >> uniform_name;
				if (type == "vec3")
				{
					vec3 vec;
					stream >> vec.x >> vec.y >> vec.z;
					material->set_vec3(uniform_name, vec);
					continue;
				}
				else if (type == "vec4")
				{
					vec4 vec;
					stream >> vec.x >> vec.y >> vec.z >> vec.w;
					material->set_vec4(uniform_name, vec);
					continue;
				}
			}
		}
	}
}

Material* ResourceManager::load_material(const std::string& name, const std::string& shader_name)
{
	Shader* shader = shaders[shader_name].get();
	if (!shader)
	{
		std::cout << "Could not find shader - " << shader_name << " - while creating material: " << name << std::endl;
	}
	materials[name] = std::make_unique<Material>(shader);
	return materials[name].get();
}

Mesh* ResourceManager::get_mesh(const std::string& name)
{
	if (!meshes.contains(name))
	{
		return nullptr;
	}
	return meshes.at(name).get();
}

Shader* ResourceManager::get_shader(const std::string& name)
{
	if (!shaders.contains(name))
	{
		return nullptr;
	}
	return shaders.at(name).get();
}

Material* ResourceManager::get_material(const std::string& name)
{
	if (!materials.contains(name))
	{
		return nullptr;
	}
	return materials.at(name).get();
}

ResourceManager* ResourceManager::get()
{
	return s_instance.get();
}

Mesh* ResourceManager::load_mesh(const std::string& name, const std::string& file_path)
{
	meshes[name] = std::make_unique<Mesh>(file_path);
	return meshes[name].get();
}

Shader* ResourceManager::load_shader(const std::string& name, const std::string& file_path)
{
	shaders[name] = std::make_unique<Shader>(file_path);
	return shaders[name].get();
}

