#version 460 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	//Linearly interpolate between both textures (1- mixValue wall, mixValue awesomeface)
	FragColor = texture(texture1, vec2(TexCoord.x,1.0-TexCoord.y)) * vec4(ourColor, 1.0);
}

