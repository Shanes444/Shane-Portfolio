#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec2 ourColor;
out vec2 TexCoord;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x,-aTexCoord.y);
}