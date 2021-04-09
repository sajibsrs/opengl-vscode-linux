#version 440 core
out vec4 fragColor;

in vec3 colorData;
in vec2 texCoord;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    fragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord) * vec4(colorData, 1.0), 0.3); // * vec4(colorData, 1.0)
}
