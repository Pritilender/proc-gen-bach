#version 440
in vec3 Position;
in vec3 Normal;
in vec2 UV;

out vec4 FragColor;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;

uniform sampler2DArray textures;

float changeRange(float oldValue, float oldMin, float oldMax, float newMin, float newMax) {
    return (((oldValue - oldMin) * (newMax - newMin)) / (oldMax - oldMin)) + newMin;
}

float getMixFactor(float alt, float layerStart, float layerEnd) {
    return changeRange(alt, layerStart, layerEnd, 0, 1);
}

void getLayer(vec3 position, out int layer, out float mixFactor) {
    if (position.y < -0.3) {
        layer = 0;
        mixFactor = getMixFactor(position.y, -5, -0.3);
    } else if (position.y < 0.0) {
        layer = 1;
        mixFactor = getMixFactor(position.y, -0.3, 0.0);
    } else if (position.y < 0.1) {
        layer = 2;
        mixFactor = getMixFactor(position.y, 0.0, 0.1);
    } else if (position.y < 1.0) {
        layer = 3;
        mixFactor = getMixFactor(position.y, 0.1, 1.0);
    } else if (position.y < 4) {
        layer = 4;
        mixFactor = getMixFactor(position.y, 1.0, 4.0);
    } else if (position.y < 5) {
        mixFactor = getMixFactor(position.y, 4.0, 5.0);
        layer = 5;
    } else if (position.y < 8) {
        layer = 6;
        mixFactor = getMixFactor(position.y, 5.0, 8.0);
    } else {
        layer = 7;
        mixFactor = getMixFactor(position.y, 8.0, 10.0);
    }
}

vec3 ads() {
    vec4 LightPosition = ViewMatrix * vec4(1000.0f, 0.0f, 1000.0f, 1.0f);
    vec3 LightIntensity = vec3(0.7f, 0.7f, 0.7f);
    int layer;
    float mixF;
    getLayer(Position, layer, mixF);
    int nextLayer = (layer + 1) == 8 ? 7 : layer + 1;
    vec3 thisTexD = texture(textures, vec3(UV.x, UV.y, layer)).xyz;
    vec3 nextTexD = texture(textures, vec3(UV.x, UV.y, nextLayer)).xyz;

    vec3 Kd = mix(thisTexD, nextTexD, mixF);
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
