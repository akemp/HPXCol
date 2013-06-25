#version 330

uniform mat4 projection;
uniform mat4 modelview;
uniform mat4 model;

layout(location = 0) in vec3 vert1;
layout(location = 1) in vec2 tex_coords;
layout(location = 2) in vec3 normal_modelspace;

out vec2 tex_coords_frag;

void main()
{
    vec4 pos = vec4(vert1, 1.0);

	vec4 position =  pos;

	tex_coords_frag = tex_coords;	

	gl_Position = projection * model * position;
}
