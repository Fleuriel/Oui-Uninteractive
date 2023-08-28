/* !
@file    my-tutorial-4.vert
@author  tan.a@digipen.edu
@date	 01/06/2023

This file contains a vertex shader program that takes in per-vertex postion
and color attribute and outputsthe position as well as the color
*//*__________________________________________________________________________*/

#version 450 core


/**

@brief Specifies the input vertex attribute for position in the vertex shader.
       The aVertexPosition input variable in the vertex shader is associated with 
       location 0, which corresponds to the input position attribute. This 
       association is performed using the layout (location=0) in 
       vec2 aVertexPosition; declaration.

       It is called using the function:
       glEnableVertexArrayAttrib(vaoid, 8);
*/


layout (location=0) in vec2 aVertexPosition;


/**

@brief Specifies the input vertex attribute for color in the vertex shader.
       The aVertexColor input variable in the vertex shader is associated with 
       location 1, which corresponds to the input color attribute. This 
       association is performed using the layout (location=1) in 
       vec3 aVertexColor; declaration.
       
       It is called using the function:
       glEnableVertexArrayAttrib(vaoid, 9);
*/
layout (location=1) in vec3 aVertexColor;


/**

@brief Specifies the output vertex attribute for color in the vertex shader.
       The vColor output variable in the vertex shader is associated with 
       location 0, which corresponds to the output color attribute. This 
       association is performed using the layout (location=0) out vec3 vColor; 
       declaration.
*/
layout (location=0) out vec3 vColor;

//declare a uniform mat3
uniform mat3 uModel_to_NDC;



/*  _________________________________________________________________________ */
/*! main

@brief
the main function of the shader program
which sets the position and color of the vertex transformation matrix
and the input attributes

@param none

@return none


*/
void main(void){

	//set the position
	gl_Position = vec4(vec2(uModel_to_NDC * vec3(aVertexPosition, 1.f)), 0.0, 1.0);
	//set the color
	vColor = aVertexColor;
}