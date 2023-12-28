#version 460 core

struct Particle {
	vec4 pos;
	vec4 color;
};

layout(std430, binding = 0) readonly buffer ParticlesBuffer {
	Particle[] particles;
};

out VS_OUT {
	vec3 color;
} vs_out;

void main(){
	gl_Position = particles[gl_VertexID].pos;
	vs_out.color = particles[gl_VertexID].color.rgb;
}