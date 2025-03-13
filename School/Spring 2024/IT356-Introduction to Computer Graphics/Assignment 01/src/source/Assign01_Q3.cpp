#include "loadShaders.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define M_PI 3.14159265358979323846264338327950288   /* pi */


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

//Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
	
//Vertex Buffer Object (VBO)
unsigned int VBO;

//Vertex Array Object (VAO)
unsigned int VAO;

unsigned int EBO;

//Shader Program (shaderProgram)'s ID
int shaderProgram;

//tells the program which position, or "mode" the graphics should be in
int mode;

void init(void)
{
	mode = 0;
	//Return shaderProgram, which is used to set programID
	shaderProgram = loadShader("../../src/shader/q3_vshader.glsl",
		"../../src/shader/q3_fshader.glsl");

	//Set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
		//positions         //colors
		0.0f, 0.8f, 0.0f,  0.0f, 1.0f, 1.0f, //top
	   -0.5f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f, //bottom left
		0.5f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  //top 
		0.5f, 0.8f, 0.0f,  1.0f, 1.0f, 0.0f, 
		0.0f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f 
	};

	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3,
		1, 2, 4
	};

	//Generate VAO and VBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Bind VAO and VBO
	//Bind the Vertex Array Object first, 
	//then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Use shderProgram
	//We only have a single shader 
	//we could also just activate our shader once beforehand if we want to 
	glUseProgram(shaderProgram);

	//Wireframe polygons.
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void display()
{
	
	//Render
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(VAO);

	glm::mat4 transform = glm::mat4(1.0f);

	//Draw the triangle
	if (mode == 0) {
		transform = glm::scale(transform, glm::vec3(1, 1, 1));
		unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	}
	else if (mode == 1) {
		transform = glm::scale(transform, glm::vec3(1, 1, 1));
		unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	else if (mode == 2) {
		transform = glm::scale(transform, glm::vec3(-1, 1, 1));
		unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
		
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		
	}
	else if (mode == 3) {
		
		transform = glm::scale(transform, glm::vec3(-1, 1, 1));
		unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	}
	else if (mode == 4) {
		
		transform = glm::scale(transform, glm::vec3(1, -1, 1));
		unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
	}
	else if (mode == 5) {
		transform = glm::scale(transform, glm::vec3(-1, -1, 1));
		unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
	}
	
}

int main()
{
	//glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, 
			"Assign 01: Q3 Stevens", NULL, NULL);
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

		//glfw: swap buffers and poll IO events 
		//(keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Optional: de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	//glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}

//Process all input: query GLFW whether relevant keys are pressed/released 
//this frame and react accordingly
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		mode = 0;
	}
	else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
	{
		mode = 1;
	}
	else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		mode = 2;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		mode = 3;
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		mode = 4;
	}
	else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		mode = 5;
	}
}


//glfw: whenever the window size changed (by OS or user resize) this 
//callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//Make sure the viewport matches the new window dimensions; note that width and 
	//height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

