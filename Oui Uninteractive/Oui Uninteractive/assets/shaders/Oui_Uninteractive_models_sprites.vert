#version 450 core


layout (location=0) in vec2 aVertexPosition;
layout (location=1) in vec3 aVertexColor;
layout (location=2) in vec2 aVertexTexture;

layout (location=0) out vec3 vColor;
layout (location=1) out vec2 vTex;

uniform mat3 uModel_to_NDC;

uniform int fr;
uniform int r;
uniform int c;

void main(void){

	//set the position
	gl_Position = vec4(vec2(uModel_to_NDC * vec3(aVertexPosition, 1.f)), 0.0, 1.0);
	//set the color
	vColor = aVertexColor;

    vTex = vec2(aVertexTexture.x,0);

	// Set the texture to the 'bytes'
	//vTex = aVertexTexture;

}