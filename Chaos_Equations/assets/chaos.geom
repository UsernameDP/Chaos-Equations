#version 460 core
layout (points) in;
layout (line_strip, max_vertices = 100) out;

struct Particle {
	vec4 pos;
	vec4 color;
	vec4 history[99]; 
};

layout(std430 , binding = 0) buffer ParticlesBuffer {
	Particle[] particles;
};

in VS_OUT {
    uint index;
} gs_in[];  

uniform mat4 VP;

out vec4 fragColor;

void main() {    
	uint index = gs_in[0].index;
	vec4 color = particles[index].color;

    for (uint i = 0; i < particles[index].history.length(); i++) {
        float interpFactor = float(i) / float(particles[index].history.length() - 1);
        vec4 currentPos = particles[index].history[i];
        gl_Position = VP * currentPos;
        fragColor = mix(vec4(0.0, 0.0, 0.0, 1.0), color, interpFactor); // Adjust the colors based on your preference
        EmitVertex();
    }

    gl_Position = VP * particles[index].pos;
	fragColor = color;
    EmitVertex();

    EndPrimitive();
}  