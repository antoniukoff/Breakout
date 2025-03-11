#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv_coords;
layout(location = 2) in float i_opacity;
	
out vec2 tex_coords;
out float opacity;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	opacity = i_opacity;
	tex_coords = uv_coords;
	gl_Position = projection * view * vec4(position, 1.0);
}

#shader fragment

#version 330 core

in vec2 tex_coords;
in float opacity;

out vec4 frag_color;

uniform sampler2D texture_0;
uniform sampler2D texture_1;

void main()
{
	vec4 color = mix(texture(texture_0, tex_coords), texture(texture_1, tex_coords), 0.5);
	frag_color = opacity * color;
}
