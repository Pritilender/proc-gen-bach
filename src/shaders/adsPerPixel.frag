#version 440
in vec3 Position;
in vec3 Normal;

out vec4 FragColor;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;

vec3 getDiffuseColor(vec3 position) {
    vec3 diffuse;
    if (position.y < -0.3) {
        diffuse = vec3(0.0, 0.0, 0.8);
    } else if (position.y < 0.0) {
        diffuse = vec3(0.3, 0.7, 0.9);
    } else if (position.y < 0.1) {
        diffuse = vec3(0.9, 0.7, 0.4);
    } else if (position.y < 0.8) {
        diffuse = vec3(0, 0.6, 0.3);
    } else {
        diffuse = vec3(1.0, 1.0, 1.0);
    }
    return diffuse;
}

vec3 ads() {
    vec4 LightPosition = ViewMatrix * vec4(1000.0f, 0.0f, 1000.0f, 1.0f);
    vec3 LightIntensity = vec3(0.7f, 0.7f, 0.7f);
    vec3 Kd = getDiffuseColor(Position);
    vec3 Ka = Kd - 0.2;
    vec3 Ks = vec3(0.2, 0.2, 0.2);
    float Shininess = 1.0f;

    vec3 n = normalize( Normal );
    vec3 s = normalize(vec3(LightPosition)); // directional
    vec3 VMPosition = vec3(ViewMatrix * ModelMatrix * vec4(Position, 1.0));
    vec3 v = normalize(vec3(-VMPosition));
    vec3 h = normalize(v + s);

    return LightIntensity * (Ka + Kd * max(dot(s, n), 0.0) + Ks * pow(max(dot(h, n), 0.0), Shininess));
}

void main() {
    FragColor = vec4(ads(), 1.0);
}
