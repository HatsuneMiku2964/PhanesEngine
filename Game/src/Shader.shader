#shader vertex
#version 330 core

layout(location = 0) in vec2 position;

uniform vec3 u_color;

uniform mat4 u_view_proj;
uniform mat4 u_model;

out vec3 vColor;

void main()
{
	gl_Position = u_view_proj * u_model * vec4(position, 0, 1);
	vColor = u_color;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 vColor;

void main()
{
	color = vec4(vColor, 1);
}