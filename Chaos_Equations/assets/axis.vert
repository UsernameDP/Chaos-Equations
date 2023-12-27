#version 430 core

layout(location = 0) in vec3 aPos;

uniform float radius;
uniform mat4 VP;

out vec3 fragColor;

void main() {
    fragColor = aPos + 0.25;
    gl_Position = VP * vec4(aPos * radius, 1.0);
}
