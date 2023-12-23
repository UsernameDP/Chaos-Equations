#version 330 core

in vec3 fragColor; // Input color from vertex shader

out vec4 finalColor; // Output color to framebuffer

uniform float time;

void main() {
    finalColor = vec4(fragColor * time, 1.0);
}
