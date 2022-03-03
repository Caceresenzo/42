#version 330 core

layout(location = 0) in vec2 in_Positions;
layout(location = 1) in vec2 in_UV;

out vec2 pass_UV;

uniform ivec2 windowSize;

void main(){
	vec2 half = windowSize / 2;
	vec2 homoneneous = (in_Positions - half) / half;
	
	gl_Position = vec4(homoneneous, 0, 1);

	pass_UV = in_UV;
}
