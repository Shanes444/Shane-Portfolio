#version 460 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

float mixValue = .5;

void main()
{
	//Linearly interpolate between both textures (1- mixValue wall, mixValue awesomeface)
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(TexCoord.x,TexCoord.y)), mixValue) * vec4(ourColor, 1.0);
}

