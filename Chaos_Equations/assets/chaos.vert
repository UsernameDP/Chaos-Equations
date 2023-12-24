#version 430
struct Particle {
	vec4 pos;
	vec4 color;
	vec4 history[99]; 
};

layout(std430 , binding = 0) buffer ParticlesBufer {
	Particle[] particles;
};

void main(){
	
}
