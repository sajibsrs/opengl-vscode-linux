#version 440 core
layout (location = 0) in vec3 attrPos;
layout (location = 1) in vec3 attrColor;

out vec3 colorData;

void main()
{
    gl_Position = vec4(attrPos, 1.0);
    colorData = attrColor;
}
