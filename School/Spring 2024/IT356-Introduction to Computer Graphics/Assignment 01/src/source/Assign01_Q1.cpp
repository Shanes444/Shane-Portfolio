#include "loadShaders.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

//Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//Vertex Buffer Object (VBO)
unsigned int VBOs[2];

//Vertex Array Object (VAO)
unsigned int VAOs[2];

//Shader Program (shaderProgram)'s ID
unsigned int shaderProgram1;
unsigned int shaderProgram2;

//Variables for shader adjustment
GLint nChangeCol;
float timeValue1;
float timeValue2;


void init(void)
{
	//Initialize variables for shader adjustment
	nChangeCol = 2;


	//Return shaderProgram, which is used to set the shader program's ID
	//i.e., shaderProgram1 and shaderProgram2
	shaderProgram1 = loadShader("../../src/shader/q1_triangles1.vert",
		"../../src/shader/q1_triangles1.frag");
	shaderProgram2 = loadShader("../../src/shader/q1_triangles2.vert",
		"../../src/shader/q1_triangles2.frag");


	//Set up vertex data (and buffer(s)) and configure vertex attributes
	float firstTriangle[] = {
   -0.90f, -0.90f, 0.0f,
	0.825f, -0.90f, 0.0f,
   -0.90f,  0.90f, 0.0f,
	};
	float secondTriangle[] = {
		0.90f, -0.90f, 0.0f,
		0.90f,  0.90f, 0.0f,
	   -0.825f,  0.90f, 0.0f,
	};

	//We can generate multiple VAOs and VBOs at the same time
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);

	//First triangle setup
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);

	//Vertex attributes stay the same
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//The Second triangle setup
	glBindVertexArray(VAOs[1]);//Note that we bind to a different VAO now
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);//And a different VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);

	//Because the vertex data is tightly packed
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Wireframe polygons.
	//glLineWidth(6);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void display()
{
	//Render
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//When we draw the triangle we first use the vertex and orange fragment shader from the first program
	glUseProgram(shaderProgram1);

	//Draw the first triangle using the data from our first VAO
	glBindVertexArray(VAOs[0]);

	//This call should output the first triangle
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//Variable used to update shader uniform
	timeValue1 = 0.0f;
	timeValue2 = 0.0f;

	if (nChangeCol == 0) {
		timeValue1 = glfwGetTime();
	}
	else if (nChangeCol == 1) {
		timeValue1 = 0.0f;
	}
	else if (nChangeCol == 2) {
		timeValue1 = 0.0f;
	}

	//Transfer data to shader
	int timeLoc1 = glGetUniformLocation(shaderProgram1, "timeVal1");
	glUniform1f(timeLoc1, timeValue1);
	
	//Then we draw the second triangle using the data from the second VAO
	//When we draw the second triangle we want to use a different shader program so we switch 
	glUseProgram(shaderProgram2);
	glBindVertexArray(VAOs[1]);


	//This call should output the second triangle
	glDrawArrays(GL_TRIANGLES, 0, 3);

	if (nChangeCol == 0) {
		timeValue2 = 0.0f;
	}
	else if (nChangeCol == 1) {
		timeValue2 = glfwGetTime();
	}
	else if (nChangeCol == 2) {
		timeValue2 = 0.0f;
	}

	int timeLoc2 = glGetUniformLocation(shaderProgram2, "timeVal2");
	glUniform1f(timeLoc2, timeValue2);

	//No need to unbind it every time 
	glBindVertexArray(0);
}

int main()
{
	//glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Assign01: Q1 Stevens", NULL, NULL);
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

	//Deallocate all resources by deleting VAO and VBO objects
	//Optional: de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);


	//glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}

//Process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		nChangeCol = 0;
	}
	else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
	{
		nChangeCol = 1;
	}
	else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		nChangeCol = 2;
	}

}

//glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//Make sure the viewport matches the new window dimensions; note that width and 
	//height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

