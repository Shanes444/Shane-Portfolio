#version 460 core

//The position variable has attribute position 0
layout (location = 0) in vec3 aPos;   
//The color variable has attribute position 1
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
uniform mat4 transform;

void main()
{
    //gl_Position = vec4(aPos, 1.0); 
    gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);

    //Output a color to the fragment shader
    //ourColor = aColor; 
    ourColor = vec3(aColor.r, aColor.g, aColor.b);
}

