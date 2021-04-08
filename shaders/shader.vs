#version 440 core
layout (location = 0) in vec3 attrPos;
layout (location = 1) in vec3 attrColor;
layout (location = 2) in vec2 attrTexCoord;

out vec3 colorData;
out vec2 texCoord;

void main()
{
    gl_Position = vec4(attrPos, 1.0);
    colorData = attrColor;
    texCoord = vec2(attrTexCoord.x, attrTexCoord.y);
}
