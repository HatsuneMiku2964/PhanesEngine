#shader vertex
#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 tex_coord;

uniform mat4 u_view_proj;

out vec4 v_color;
out vec2 v_tex_coord;

void main()
{
	gl_Position = u_view_proj * vec4(position, 0, 1);
	v_color = color;
	v_tex_coord = tex_coord;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_color;
in vec2 v_tex_coord;

uniform vec4 u_color;
//uniform sampler2D u_tex;
uniform float u_tile;

void main()
{
	//color = texture(u_tex, v_tex_coord * u_tile) * u_color;
	color = v_color;
	//color = vec4(v_tex_coord, 0.f, 1.f);
}