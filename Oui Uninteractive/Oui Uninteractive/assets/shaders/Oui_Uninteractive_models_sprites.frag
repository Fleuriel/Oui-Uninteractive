#version 450 core

layout (location=0) in vec3 vInterpColor;
layout (location=1) in vec2 vTexCoord;


in vec3 FragPos;
layout (location=0) out vec4 fFragColor;

uniform sampler2D uTex2d;


void main () {


	vec4 frag_color = texture(uTex2d, vTexCoord) ;


	fFragColor = frag_color ;
	

}