#include "Mesh.h"
#include <memory>
#include <gl/glew.h>
#include <sstream>
#include <fstream>
#include <cassert>

Mesh::Mesh(const std::string& file_path)
{
	parse_obj(file_path);
}

Mesh::Mesh(const std::vector<float> data)
{
	m_vao = std::make_unique<VertexArray>();

	/// Create VBO
	std::unique_ptr<VertexBuffer> buffer = std::make_unique<VertexBuffer>();
	buffer->upload_data(data);

	/// Create Layout
	VertexLayout layout = {
		{0, 3, GL_FLOAT, GL_FALSE},
		{1, 2, GL_FLOAT, GL_FALSE},
		{2, 3, GL_FLOAT, GL_FALSE},
	};

	m_vertex_count = data.size() * sizeof(float) / layout.get_vertex_stride();

	/// Set VBO and Layout to VAO
	m_vao->complete_setup(std::move(buffer), layout);
}

Mesh::Mesh(Mesh&& other) noexcept
	: m_vao(std::move(other.m_vao))
	, m_vertex_count(other.m_vertex_count)
{
	other.m_vertex_count = 0;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept
{
	if (this != &other)
	{
		m_vao = std::move(other.m_vao);
		m_vertex_count = other.m_vertex_count;

		other.m_vertex_count = 0;
	}
	return *this;
}

void Mesh::bind() const
{
	m_vao->bind();
}

void Mesh::unbind() const
{
	m_vao->unbind();
}

uint32_t Mesh::get_vertex_count() const
{
	return m_vertex_count;
}

void Mesh::parse_obj(const std::string& file_path)
{
	std::vector<vec3> positions;
	std::vector<vec2> tex_coords;
	std::vector<vec3> normals;

	std::ifstream ifs(file_path);
	std::string line;

	std::vector<Face> faces;

	while (std::getline(ifs, line)) 
	{
		std::istringstream stream(line);
		std::string type;
		stream >> type;
		if (type == "v") 
		{
			vec3 p;
			stream >> p.x >> p.y >> p.z;
			positions.push_back(p);
		}
		else if (type == "vt") 
		{
			vec2 uv;
			stream >> uv.x >> uv.y;
			tex_coords.push_back(uv);
		}
		else if (type == "vn") 
		{
			vec3 n;
			stream >> n.x >> n.y >> n.z;
			normals.push_back(n);
		}
		else if (type == "f") 
		{
			std::vector<std::string> faces_info;
			std::string face_token;
			while (stream >> face_token)
			{
				faces_info.push_back(face_token);
			}
			Face face = process_face(faces_info, positions, tex_coords, normals);
			faces.push_back(face);
		}
	}
	ifs.close();

	create_mesh(faces, GL_STATIC_DRAW);
}
	
Face Mesh::process_face(
	const std::vector<std::string>& faces_info, 
	const std::vector<vec3>& positions,
	const std::vector<vec2>& uvs,
	const std::vector<vec3>& normals
	)
{
	assert(faces_info.size() == 3);

	Face face;

	for (int i = 0; i < 3; ++i)
	{
		std::istringstream stream(faces_info[i]);
		std::string part;

		std::getline(stream, part, '/');
		face.v[i].position = positions[std::stoi(part) - 1];

		if (std::getline(stream, part, '/') && !part.empty())
		{
			face.v[i].uv = uvs[std::stoi(part) - 1];
		}

		if (std::getline(stream, part, '/') && !part.empty())
		{
			face.v[i].normal = normals[std::stoi(part) - 1];
		}
	}
	return face;
}

void Mesh::create_mesh(const std::vector<Face>& faces, uint32_t usage_mode)
{
	m_vao = std::make_unique<VertexArray>();

	/// Create VBO
	std::unique_ptr<VertexBuffer> buffer = std::make_unique<VertexBuffer>();

	/// Create Layout
	VertexLayout layout = {
		{0, 3, GL_FLOAT, GL_FALSE},
		{1, 2, GL_FLOAT, GL_FALSE},
		{2, 3, GL_FLOAT, GL_FALSE},
	};

	m_vertex_count = faces.size() * 3;

	buffer->upload_data(faces);
	/// Set VBO and Layout to VAO
	m_vao->complete_setup(std::move(buffer), layout);
}





