#shader vertex
#version 460 core

const int NUM_LIGHTS = 1;

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uvs;
layout(location = 2) in vec3 normal;

uniform mat4 model_matrix;
struct Light
{
	vec4 padding3;

	vec3 position;
	float padding;
	vec4 color;

	float constant;
    float linear;
    float quadratic;

	float padding2;
};
layout(std140, binding = 1) uniform SceneData
{
    mat4 projection_matrix;
    mat4 view_matrix;

	vec3 camera_world;
	float padding;
	 
	Light lights[NUM_LIGHTS];
};

out vec3 frag_world;
out vec3 frag_normal;

void main()
{
	frag_world = vec3(model_matrix * vec4(position, 1.0));

	mat3 mat_normal = mat3(transpose(inverse(model_matrix)));
	frag_normal = normalize(mat_normal * normal);

	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(position, 1.0);
}

#shader fragment
#version 460 core

const int NUM_LIGHTS = 1;

in vec3 frag_world;
in vec3 frag_normal;

struct Light
{
	vec4 padding3;

	vec3 position;
	float padding;
	vec4 color;

	float constant;
    float linear;
    float quadratic;

	float padding2;
};

struct Material
{
	float ambient_strength;
	float diffuse_strength;
	float specular_strength;
	float shininess;

	vec4 color;
};

layout(std140, binding = 1) uniform SceneData
{
    mat4 projection_matrix;
    mat4 view_matrix;

	vec3 camera_world;
	float padding;

	Light lights[NUM_LIGHTS];
};

uniform Material material;

out vec4 frag_color;

void main()
{
	vec4 out_color = vec4(0.0);

	for(int i = 0; i < NUM_LIGHTS; i++)
	{
		float dist = length(lights[i].position - frag_world);
		float attenuation = 1.0 / (lights[i].constant + lights[i].linear * dist + lights[i].quadratic * (dist * dist));
		
		/// Ambient
		vec4 ambient = vec4(material.ambient_strength);

		/// Diffuse
		vec3 light_dir = normalize(lights[i].position - frag_world);
		float diff_factor  = max(dot(light_dir, frag_normal), 0.0);

		vec4 diffuse = lights[i].color * diff_factor * material.diffuse_strength;

		/// Specular
		vec3 camera_dir = normalize(camera_world - frag_world);
		vec3 reflect_vec = reflect(-light_dir, frag_normal);
		float spec_factor = pow(max(dot(reflect_vec, camera_dir), 0.0), material.shininess);

		vec4 specular =  lights[i].color * spec_factor * material.specular_strength;

		diffuse *= attenuation;
		specular *= attenuation;

		out_color += (ambient + diffuse + specular);
	}

	/// Final Color
	frag_color = vec4(out_color.rgb * material.color.rgb, 1.0);
}
