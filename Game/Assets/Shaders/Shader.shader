// A basic shader

#shader vertex
#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 tex_coord;

uniform vec3 u_color;

uniform mat4 u_view_proj;
uniform mat4 u_model;

out vec3 v_Color;
out vec2 v_tex_coord;

void main()
{
	gl_Position = u_view_proj * u_model * vec4(position, 0, 1);
	v_Color = u_color;
	v_tex_coord = tex_coord;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Color;
in vec2 v_tex_coord;

uniform sampler2D u_tex;

void main()
{
	color = texture(u_tex, v_tex_coord);
}