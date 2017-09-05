#version 440

in vec4 position;

out VS_OUT {
    vec4 color;
} vs_out;

uniform mat4 modelView;
uniform mat4 projection;

void main()
{
	gl_Position = projection * modelView * position;
	vs_out.color = position * 2.0 + vec4(0.5, 0.5, 0.5, 0.0);
}
