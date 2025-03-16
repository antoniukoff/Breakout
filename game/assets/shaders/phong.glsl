#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 uvs;
layout(location = 2) in vec3 normal;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;

uniform vec3 light_position;

out vec3 fragment_pos;
out vec3 normal_dir;
out vec3 light_pos;

void main()
{
	fragment_pos = vec3(view_matrix * model_matrix * vec4(position, 1.0));

	normal_dir = normalize(mat3(transpose(inverse(view_matrix * model_matrix))) * normal);
	light_pos = vec3(view_matrix * vec4(light_position, 1.0));

	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(position, 1.0);
}

#shader fragment

#version 330 core

in vec3 fragment_pos;
in vec3 normal_dir;
in vec3 light_pos;

out vec4 frag_color;

uniform vec4 model_color;
uniform vec4 light_color;

void main()
{
	/// Ambient
	vec4 ambient = light_color * 0.1;

	/// Diffuse
	vec3 light_direction = normalize(light_pos - fragment_pos);
	float d_coefficient  = max(dot(light_direction, normal_dir), 0.0);

	vec4 diffuse = light_color * d_coefficient;

	/// Specular
	vec3 viewer_dir = normalize(-fragment_pos);
	vec3 reflect_vec = reflect(-light_direction, normal_dir);
	float spec_coeff = pow(max(dot(reflect_vec, viewer_dir), 0.0), 96.0);

	vec4 spec = 1.0 * spec_coeff * light_color;

	/// Final Color
	frag_color = vec4(vec4((ambient + diffuse + spec) * model_color).xyz, 1.0);
}
