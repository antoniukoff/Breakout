#shader vertex
#version 460 core

const int NUM_LIGHTS = 5;

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;

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


layout(std140, binding = 1) uniform LightBuffer
{
    mat4 projection_matrix;
    mat4 view_matrix;

	vec3 camera_world;
	float padding;

	Light lights[NUM_LIGHTS];
};

uniform mat4 model_matrix;

void main()
{
	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(aPos, 1.0);
}

#shader fragment

#version 460 core

const int NUM_LIGHTS = 5;

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

layout(std140, binding = 1) uniform LightBuffer
{
    mat4 projection_matrix;
    mat4 view_matrix;

	vec3 camera_world;
	float padding;

	Light lights[NUM_LIGHTS];
};

uniform int index;

out vec4 frag_color;

void main()
{
	frag_color = lights[index].color;
}
