#version 460 core
layout(points) in;
layout(points, max_vertices = 1) out;

uniform mat4 VP;


in VS_OUT {
	vec3 color;
} gs_in[];

out vec3 fragColor;

void main(){
	fragColor = gs_in[0].color;
	gl_Position = VP * gl_in[0].gl_Position;
	EmitVertex();
	EndPrimitive();
}