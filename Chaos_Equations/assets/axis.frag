#version 460 core

in vec3 fragColor;
out vec4 finalColor; // Output color to framebuffer

void main() {
    finalColor =  vec4(fragColor, 1.0);
}
