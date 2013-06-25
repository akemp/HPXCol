#version 330

uniform sampler2D tex;

in vec2 tex_coords_frag;
out vec4 color;
void main()
{
    vec4 col = vec4(texture(tex,tex_coords_frag));
	color = col;
}
