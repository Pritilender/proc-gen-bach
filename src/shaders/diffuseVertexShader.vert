#version 440

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 LightIntensity;

uniform vec4 LightPosition; // in eye coords
uniform vec3 Kd; // diffuse reflectivity
uniform vec3 Ld; // light source intensity

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform mat3 NormalMatrix; // inverse transpose mat of ModelView upper 3x3

void main() {
	vec3 tnorm = normalize(NormalMatrix * VertexNormal);
	vec4 eyeCoords = View * Model * vec4(VertexPosition, 1.0);
	vec3 s = normalize(vec3(LightPosition - eyeCoords));
	LightIntensity = Ld * Kd * max(dot(s, tnorm), 0.0);
	gl_Position = Projection * View * Model * vec4(VertexPosition, 1.0);
}
