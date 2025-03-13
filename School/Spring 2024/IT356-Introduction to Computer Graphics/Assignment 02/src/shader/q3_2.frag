#version 460 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture3;
uniform sampler2D texture4;

void main()
{
	//Linearly interpolate between both textures
	FragColor = mix(texture(texture3, TexCoord), texture(texture4, TexCoord), 0.5f);
}

