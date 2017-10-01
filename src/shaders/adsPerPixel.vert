#version 440

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 Position;
out vec3 Normal;
out vec2 UV;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform float xMax;
uniform float resolution;

void main() {
    Normal = normalize(NormalMatrix * VertexNormal);
    Position = VertexPosition;
    float u = Position.x / xMax * (resolution - 1);
    float v = Position.z / xMax * (resolution - 1);
    UV = vec2(u, v);
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(VertexPosition, 1.0);
}
