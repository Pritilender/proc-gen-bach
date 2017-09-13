#version 440

struct LightInfo {
    vec4 Position; // light position in eye coords
    vec3 La; // ambient intensity
    vec3 Ld; // diffuse intensity
    vec3 Ls; // specular intensity
};

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec3 AmbientColor;
layout (location = 3) in vec3 DiffuseColor;
layout (location = 4) in vec3 SpecularColor;

//out vec3 LightIntensity;
flat out vec3 LightIntensity;

uniform LightInfo Light;
uniform float Shininess;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;

void main() {
	vec3 tnorm = normalize(NormalMatrix * VertexNormal);
	vec4 eyeCoords = ViewMatrix * ModelMatrix * vec4(VertexPosition, 1.0);
//	vec3 s = normalize(vec3(Light.Position - eyeCoords));
    vec3 s = normalize(vec3(Light.Position)); // use directional light
	vec3 v = normalize(-eyeCoords.xyz);
	vec3 r = reflect(-s, tnorm);
	vec3 ambient = Light.La * AmbientColor;
	float sDotN = max(dot(s, tnorm), 0.0);
	vec3 diffuse = Light.Ld * DiffuseColor * sDotN;
	vec3 spec = vec3(0.0);

	if (sDotN > 0.0) {
	    spec = Light.Ls * SpecularColor * pow(max(dot(r, v), 0.0), Shininess);
	}

	LightIntensity = ambient + diffuse + spec;
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(VertexPosition, 1.0);
}
