#version 460 core 

struct Particle {
	vec4 pos;
	vec4 color;
};

struct History {
	vec4 pos;
};

layout(std430, binding = 0) buffer ParticlesBuffer {
	Particle[] particles;
};

layout(std430, binding = 1) buffer HistoryBuffer {
	History[] history;
};

uniform mat4 VP;

void main(){
	

}