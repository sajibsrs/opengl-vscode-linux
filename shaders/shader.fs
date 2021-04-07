#version 440 core
out vec4 fragColor;

in vec3 colorData;

void main()
{
    fragColor = vec4(colorData, 1.0f);
}
