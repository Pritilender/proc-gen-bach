#version 440

struct LightInfo {
    vec4 Position; // light position in eye coords
    vec3 La; // ambient intensity
    vec3 Ld; // diffuse intensity
    vec3 Ls; // specular intensity
};

struct MaterialInfo {
    vec3 Ka; // ambient reflectivity
    vec3 Kd; // diffuse reflectivity
    vec3 Ks; // specular reflectivity
    float Shininess; // specular shininess factor
};

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

//out vec3 LightIntensity;
flat out vec3 LightIntensity;

uniform LightInfo Light;
uniform MaterialInfo Material;
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
	vec3 ambient = Light.La * Material.Ka;
	float sDotN = max(dot(s, tnorm), 0.0);
	vec3 diffuse = Light.Ld * Material.Kd * sDotN;
	vec3 spec = vec3(0.0);

	if (sDotN > 0.0) {
	    spec = Light.Ls * Material.Ks * pow(max(dot(r, v), 0.0), Material.Shininess);
	}

	LightIntensity = ambient + diffuse + spec;
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(VertexPosition, 1.0);
}
