#version 460 core

out vec4 FragColor;
in vec3 ourColor;

void main()
{
    //output a color to the frame buffer 
    //FragColor = vec4(ourColor, 1.0f);
    FragColor = vec4(ourColor.r, ourColor.g, ourColor.b, 1.0f);
}