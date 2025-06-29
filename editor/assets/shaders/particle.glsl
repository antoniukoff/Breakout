#shader vertex
#version 330 core

layout(location = 0) in vec3 position;   
layout(location = 1) in mat4 model; 
layout(location = 5) in vec4 color; 

uniform mat4 view;
uniform mat4 projection;

out vec4 f_color;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    f_color = color;
}


#shader fragment

#version 330 core

in vec4 f_color;

out vec4 frag_color;

void main()
{
	frag_color = f_color;
}
