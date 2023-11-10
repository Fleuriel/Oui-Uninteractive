#version 450 core


layout (location=0) in vec2 aVertexPosition;
layout (location=1) in vec3 aVertexColor;
layout (location=2) in vec2 aVertexTexture;

layout (location=0) out vec3 vColor;
layout (location=1) out vec2 vTex;

uniform int col_To_Draw;
uniform int rows;
uniform int cols;
uniform int row_To_Draw;

uniform mat3 uModel_to_NDC;

void main(void){

	//set the position
	gl_Position = vec4(vec2(uModel_to_NDC * vec3(aVertexPosition, 1.f)), 0.0, 1.0);
	//set the color
	vColor = aVertexColor;

	float width = aVertexTexture.x / cols;
	float height = aVertexTexture.y / rows;



	vTex = vec2(width , height) + vec2(float(col_To_Draw)/float(cols),float(row_To_Draw)/float(rows));

	//vColor = vec3(col_To_Draw,rows,cols);


	// Set the texture to the 'bytes'
	//vTex = aVertexTexture;

}