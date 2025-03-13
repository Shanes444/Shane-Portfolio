#include "loadShaders.h"
#include <stb_image.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define M_PI 3.14159265358979323846264338327950288   /* pi */

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

//Settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 1000;

//Vertex Buffer Object (VBO)
unsigned int VBOs[2];
//Vertex Array Object (VAO)
unsigned int VAOs[2];
//Element Buffer Objects
unsigned int EBOs[2];



//Shader Program (shaderProgram)'s ID
unsigned int shaderProgram1;

unsigned int shaderProgram2;

//Two texture ids
unsigned int texture1, texture2, texture3, texture4;

//Image width and height
int nWidth, nHeight;

//Aspect ratio
float ratio;

//keeps track of how much time the shapes have been moving
double transTime;

int mode;

void init(void)
{
	nWidth = SCR_WIDTH;
	nHeight = SCR_HEIGHT;

	mode = 0;

	transTime = M_PI;

	//Compute the display window ratio
	ratio = (float)nHeight / (float)nWidth;

	//Return shaderProgram, which is used to set the shader program's ID
	shaderProgram1 = loadShader("../../src/shader/q3.vert", "../../src/shader/q3.frag");

	shaderProgram2 = loadShader("../../src/shader/q3_2.vert", "../../src/shader/q3_2.frag");

	//Set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices1[] = {
		// positions                  // colors           // texture coords (note that we changed them to 2.0f!)
		-1.0f, 1.0f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right for square 1
		-1.0f, 0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f, // bottom right for square 1
		-0.5f, 0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f, // bottom left for square 1
		-0.5f, 1.0f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f  // top left for square 1
	};
	float vertices2[] = {
		1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right for square 2
		1.0f, -0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f, // bottom right for square 2
		0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f, // bottom left for square 2
		0.5f, -1.0f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f  // top left for square 2
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3, // second triangle
	};

	//Generate VAO, VBO, and EBO
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	glGenBuffers(2, EBOs);

	//Bind VAO, VBO, and EBO to array buffer
	//Create and initialize a buffer object's data store for VBO and EBO
	//by loading vertices and indices to graphics memory 
	//for square 1
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Arrange data in graphics memory using attribute pointer
	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//Texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//for square 2
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Arrange data in graphics memory using attribute pointer
	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//Texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//Load and create a texture 
	//texture 1
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	//set the texture wrapping parameters
	//set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	//Load image, create texture and generate mipmaps
	int width, height, nrChannels;

	//Tell stb_image.h to flip loaded texture's on the y-axis.
	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load("../../src/resources/textures/wall.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	//Load and create a texture 
	//texture 2
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	//set the texture wrapping parameters
	//set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	//set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	//load image, create texture and generate mipmaps
	data = stbi_load("../../src/resources/textures/face.png", &width, &height, &nrChannels, 0);

	if (data)
	{
		//note that the awesomeface.png has transparency and thus an alpha channel, 
		//so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	//Load and create a texture
	//texture 3
	glGenTextures(1, &texture3);
	glBindTexture(GL_TEXTURE_2D, texture3);
	//set the texture wrapping parameters
	//set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("../../src/resources/textures/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	//Load and create a texture 
	//texture 4
	glGenTextures(1, &texture4);
	glBindTexture(GL_TEXTURE_2D, texture4);

	//set the texture wrapping parameters
	//set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	//set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	//load image, create texture and generate mipmaps
	data = stbi_load("../../src/resources/textures/awesomeface.png", &width, &height, &nrChannels, 0);

	if (data)
	{
		//note that the awesomeface.png has transparency and thus an alpha channel, 
		//so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	//Texture unit binding
	//Tell OpenGL for each sampler to which texture unit it belongs to 
	//(only has to be done once)
	glUseProgram(shaderProgram1);
	glUseProgram(shaderProgram2);
	
	glUniform1i(glGetUniformLocation(shaderProgram1, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram1, "texture2"), 1);

	glUniform1i(glGetUniformLocation(shaderProgram2, "texture3"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram2, "texture4"), 1);
}

void display()
{
	//Render
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//Bind textures on corresponding texture units
	//Activate the texture unit first before binding texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	
	
	//Render container
	glUseProgram(shaderProgram1);


	glUseProgram(shaderProgram2);

	glm::mat4 transform1 = glm::mat4(1.0f);
	transform1 = glm::scale(transform1, glm::vec3(-1.0f, 1.0f, 1.0f));
	transform1 = glm::translate(transform1, glm::vec3(1.5f, -abs(sin(transTime) * 1.5f), 0.0f));

	if (mode == 1) {
		transTime += 0.0005f;
	}
	
	unsigned int transformLoc1 = glGetUniformLocation(shaderProgram1, "transform");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(transform1));

	glBindVertexArray(VAOs[0]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture4);

	glUseProgram(shaderProgram2);

	glm::mat4 transform2 = glm::mat4(1.0f);
	transform2 = glm::scale(transform2, glm::vec3(1.0f, -1.0f, 1.0f));
	transform2 = glm::translate(transform2, glm::vec3(0.0f, 1.5f + -abs(sin(transTime) * 1.5f), 0.0f));

	if (mode == 1) {

	}

	unsigned int transformLoc2 = glGetUniformLocation(shaderProgram2, "transform");
	glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(transform2));

	glBindVertexArray(VAOs[1]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

int main()
{
	//glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Assignment2 Q3: Shane", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	init();

	//Render loop
	while (!glfwWindowShouldClose(window))
	{
		//Input
		processInput(window);

		display();

		//glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Release resources
	//Optional: de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, VAOs);
	glDeleteBuffers(1, VBOs);
	glDeleteBuffers(1, EBOs);


	//glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}

//Process all input: query GLFW whether relevant keys are 
//pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		mode = 1;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) {
		mode = 0;
	}
}

//glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//Make sure the viewport matches the new window dimensions; note that width and 
	//height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);

	//Calcuate display ratio

	//set up vertex data (and buffer(s)) and configure vertex attributes

}

