#version 440

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out VS_OUT {
    vec4 color;
} vs_out;

uniform mat4 modelView;
uniform mat4 projection;

void main()
{
	gl_Position = projection * modelView * vec4(position, 1.0);
	vs_out.color = vec4(color, 1.0);
}
