#version 450 core

layout (location=0) in vec3 vInterpColor;
layout (location=1) in vec2 vTexCoord;



layout (location=0) out vec4 fFragColor;
layout (location=1) out vec4 fontColor;

uniform sampler2D uTex2d;
uniform vec3 textColor;



void main () {


	vec4 setColor = {0.0f, 0.0f, 0.0f, 1.0f};

	setColor = texture(uTex2d, vTexCoord);	


	fFragColor = setColor;
	
	fontColor = vec4(textColor,1.0) * setColor;

}