/* !
@file    my-tutorial-3.frag
@author  tan.a@digipen.edu
@date	 26/05/2023

This file contains a fragment shader program that takes in per-vertex postion
and color attribute and outputsthe position as well as the color
*//*__________________________________________________________________________*/


#version 450 core

/**
@brief Specifies the input vertex attribute for interpolated color in the fragment 
shader. The vInterpColor input variable in the fragment shader is associated with 
location 0, which corresponds to the interpolated color attribute. This association 
is performed using the layout (location=0) in vec3 vInterpColor; declaration.
*/

layout (location=0) in vec3 vInterpColor;


/**
@brief Specifies the output fragment attribute for the fragment color in the 
fragment shader. The fFragColor output variable in the fragment shader is associated 
with location 0, which corresponds to the fragment color attribute. This association 
is performed using the layout (location=0) out vec4 fFragColor; declaration.
*/
layout (location=0) out vec4 fFragColor;


/*  _________________________________________________________________________ */
/*! main

@brief
the main function of the shader program
which sets the color of the vertex transformation matrix
of the interpolated color

@param none

@return none


*/

void main () {
	fFragColor = vec4(vInterpColor, 1.0);
}
