#shader vertex
#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 aColor;

uniform mat4 u_view_proj;

out vec3 vColor;

void main()
{
	gl_Position = u_view_proj * vec4(position, 0, 1);
	vColor = aColor;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 vColor;

void main()
{
	color = vec4(vColor, 1);
}