#version 460 core

out vec4 FragColor;
uniform float timeVal1;

void main()
{
    FragColor = vec4(abs(sin(timeVal1)), 1.0, 0.0, 1.0);
}
