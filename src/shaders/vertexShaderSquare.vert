#version 440

layout (location = 0) in vec3 position;

uniform mat4 modelView;
uniform mat4 projection;
uniform float normalizer;

void main()
{
	gl_Position = projection * modelView * vec4(position / normalizer, 1.0);
}
