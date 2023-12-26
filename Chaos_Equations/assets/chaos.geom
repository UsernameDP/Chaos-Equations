#version 460 core
layout (points) in;
layout (points, max_vertices = 1) out;

struct Particle {
	vec4 pos;
	vec4 color;
	vec4 history[99]; 
};

layout(std430 , binding = 0) buffer ParticlesBuffer {
	Particle[] particles;
};

void main() {    
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();
    EndPrimitive();
}  