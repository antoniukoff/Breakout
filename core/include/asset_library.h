#pragma once
#include <unordered_map>
#include <string>
#include <memory>

#include "Material.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"

class asset_library
{
public:
	static void initialize(const std::string file_path);
	static asset_library& get();

public:
	mesh* get_mesh(const std::string& name);
	shader* get_shader(const std::string& name);
	material* get_material(const std::string& name);

	material get_material_instance (const std::string& name);

	void list_assets();
private:
	mesh* load_mesh(const std::string& name, const std::string& file_path);
	shader* load_shader(const std::string& name, const std::string& file_path);
	material* load_material(const std::string& name, const std::string& shader_name);

private:
	std::unordered_map < std::string, std::unique_ptr<material> > materials;
	std::unordered_map < std::string, std::unique_ptr<shader> > shaders;
	std::unordered_map < std::string, std::unique_ptr<mesh> > meshes;
	std::unordered_map < std::string, std::unique_ptr<texture> > textures;

private:
	static std::unique_ptr<asset_library> s_instance;
};

