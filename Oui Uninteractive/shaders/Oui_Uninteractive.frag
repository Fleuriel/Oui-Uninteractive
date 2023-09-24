#version 450 core

layout (location=0) in vec3 vInterpColor;
layout (location=1) in vec2 vTexCoord;


layout (location=0) out vec4 fFragColor;


uniform sampler2D uTex2d;


void main () {


	vec4 setColor = {0.0f, 0.0f, 0.0f, 1.0f};

//	setColor = vec4(vInterpColor, 1.0);
	setColor = texture(uTex2d, vTexCoord);	


	fFragColor = setColor;

	//fFragColor = vec4(vInterpColor, 1.0);


	
	

}