#version 460 core
layout(location = 0) in uint index;

out VS_OUT {
	uint index;
} vs_out;

void main(){
	vs_out.index = index;
}
