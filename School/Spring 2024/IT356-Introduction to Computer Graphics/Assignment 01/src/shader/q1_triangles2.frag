#version 460 core

out vec4 FragColor;
uniform float timeVal2;

void main()
{
    FragColor = vec4(0.0, 1.0, abs(sin(timeVal2)), 1.0);
}

