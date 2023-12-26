#version 460 core
layout(location = 0) in uint index;

struct Particle {
	vec4 pos;
	vec4 color;
	vec4 history[99]; 
};

layout(std430, binding = 0) buffer ParticlesBuffer {
	Particle[] particles;
};

uniform mat4 VP;

out vec4 fragColor;

void main(){
	gl_Position = VP * particles[index].pos;

	fragColor = particles[index].color;
}
