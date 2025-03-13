#version 460 core

out vec4 FragColor;

in vec2 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D ourTexture1;

void main()
{
	FragColor = texture(ourTexture1, TexCoord) * vec4(0.5, ourColor, 1.0);  
}

