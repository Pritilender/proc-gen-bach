#version 440
layout (location = 0) in vec3 aPos;

out vec3 position;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    position = aPos + 0.5;
}
