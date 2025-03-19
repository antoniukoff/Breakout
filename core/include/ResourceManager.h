#pragma once
#include <unordered_map>
#include <string>

#include "Material.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

class ResourceManager
{
public:
	static void initialize(const std::string file_path);
	static ResourceManager* get();

public:
	Mesh* get_mesh(const std::string& name);
	Shader* get_shader(const std::string& name);
	Material* get_material(const std::string& name);
	
private:
	Mesh* load_mesh(const std::string& name, const std::string& file_path);
	Shader* load_shader(const std::string& name, const std::string& file_path);
	Material* load_material(const std::string& name, const std::string& shader_name);

private:
	std::unordered_map < std::string, std::unique_ptr<Material> > materials;
	std::unordered_map < std::string, std::unique_ptr<Shader> > shaders;
	std::unordered_map < std::string, std::unique_ptr<Mesh> > meshes;
	std::unordered_map < std::string, std::unique_ptr<Texture> > textures;

private:
	static std::unique_ptr<ResourceManager> s_instance;
};

