#version 450 core

layout (location = 0) in vec2 aVertexPosition;
layout (location = 1) in vec3 aVertexColor;
layout (location = 2) in vec2 aVertexTexture;

layout (location = 0) out vec3 vColor;
layout (location = 1) out vec2 vTex;

uniform mat3 uModel_to_NDC;

// These uniform variables allow you to control the sprite sheet
uniform vec2 spriteSheetDimensions; // Number of columns and rows in the sprite sheet
uniform ivec2 spriteFrame; // The current frame in the sprite sheet

void main(void) {
    // Calculate the width and height of each sprite frame
    float spriteWidth = 1.0 / spriteSheetDimensions.x;
    float spriteHeight = 1.0 / spriteSheetDimensions.y;

    // Calculate the texture coordinates for the current sprite frame
    vec2 texCoord = vec2(
        aVertexTexture.x + spriteWidth * float(spriteFrame.x),
        aVertexTexture.y + spriteHeight * float(spriteFrame.y)
    );

    // Set the position
    gl_Position = vec4(vec2(uModel_to_NDC * vec3(aVertexPosition, 1.0)), 0.0, 1.0);

    // Set the color
    vColor = aVertexColor;

    // Set the texture coordinates
    vTex = texCoord;
}
