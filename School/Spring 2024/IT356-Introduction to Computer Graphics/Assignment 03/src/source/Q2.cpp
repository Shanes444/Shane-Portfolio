#include "loadShaders.h"
#include "camera.h"
#include <stb_image.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>diffuseMap
#include <glm/gtc/type_ptr.hpp>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
unsigned int loadTexture(char const * path);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

//Settings
const unsigned int SCR_WIDTH = 1800;
const unsigned int SCR_HEIGHT = 1200;

//The cube's VAO (and VBO)
//Vertex Buffer Object (VBO)
unsigned int VBO;

//Vertex Array Object (VAO)
unsigned int cubeVAO;
unsigned int lightVAO;

//Shader Program (shaderProgram)'s ID
unsigned int lightingShader;
unsigned int lampShader;

//camera
Camera camera(glm::vec3(0.0f, 0.0f, 2.5f));

//X and Y setting for mouse operation
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

//timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//lighting
glm::vec3 lightPos;
float lightPosx, lightPosy, lightPosz;

//Diffuse map and rotation control variables
unsigned int diffuseMap;

bool rotFlg1;
float angle;


void init(void)
{
	//configure global opengl state
	glEnable(GL_DEPTH_TEST);

	//Return shaderProgram, which is used to set the shader program's ID
	lightingShader = loadShader("../../src/shader/lighting_mapsQ2.vert", "../../src/shader/lighting_mapsQ2.frag");
	lampShader = loadShader("../../src/shader/lampQ2.vert", "../../src/shader/lampQ2.frag");

	//set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
		//positions           //normals            //texture coords
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		 0.0f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.5f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.0f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.5f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.0f,  0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.5f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,

		 0.0f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.5f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f
	};

	//first, configure the cube's VAO (and VBO)
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(cubeVAO);
	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//second, configure the light's VAO (VBO stays the same; 
	//the vertices are the same for the light object which is also a 3D cube)
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//note that we update the lamp's position attribute's stride 
	//to reflect the updated buffer data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Using lighting shader
	

	//Load Textures and Material Diffuse for diffuse map
	//Load textures 
	diffuseMap = loadTexture("../../src/resources/textures/container.png");

	//Load material diffuse
	glUseProgram(lightingShader);
	unsigned int materialDiffuseLoc = glGetUniformLocation(lightingShader, "material.diffuse");
	glUniform1i(materialDiffuseLoc, 0);

	//Set Initial Variable Values
	//Set initial variable values for rotation control and lighting position
	rotFlg1 = false;
	angle = 0.0f;

	lightPosx = 1.2f;
	lightPosy = 0.9f;
	lightPosz = 0.6f;

}

void display()
{
	//Render
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

	//Activate shader for the cube
	//be sure to activate the shader when setting uniforms/drawing objects
	glUseProgram(lightingShader);

	//Lighting and viewing positions
	//Lighting position
	lightPos = glm::vec3(lightPosx, lightPosy, lightPosz);
	unsigned int lightPosLoc = glGetUniformLocation(lightingShader, "light.position");
	glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);

	//Viewing position
	unsigned int cameraPosLoc = glGetUniformLocation(lightingShader, "viewPos");
	glUniform3f(cameraPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);

	//light properties
	unsigned int ambientColorLoc = glGetUniformLocation(lightingShader, "light.ambient");
	glUniform3f(ambientColorLoc, 0.3f, 0.3f, 0.3f);

	unsigned int diffuseColorLoc = glGetUniformLocation(lightingShader, "light.diffuse");
	//darken the light a bit to fit the scene
	glUniform3f(diffuseColorLoc, 1.0f + sin(glfwGetTime()/.5), abs(cos(glfwGetTime())), abs(sin(glfwGetTime()/2)));

	unsigned int specularColorLoc = glGetUniformLocation(lightingShader, "light.specular");
	glUniform3f(specularColorLoc, 1.0f, 1.0f, 1.0f);

	
	//material properties
	//specular lighting doesn't have full effect on this object's material
	unsigned int materialSpecularLoc = glGetUniformLocation(lightingShader, "material.specular");
	glUniform3f(materialSpecularLoc, 0.5f, 0.5f, 0.5f);

	unsigned int materialShininessLoc = glGetUniformLocation(lightingShader, "material.shininess");
	glUniform1f(materialShininessLoc, 256.0f);

	//view and projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	glm::mat4 view = camera.GetViewMatrix();


	unsigned int projectionLoc = glGetUniformLocation(lightingShader, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	unsigned int viewLoc = glGetUniformLocation(lightingShader, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	//world transformation
	glm::mat4 model = glm::mat4(1.0f);

	//model = glm::scale(model1, glm::vec3(1.0f));
	if (rotFlg1)
	{
		angle = (float)glfwGetTime() / 2.0;
		model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
	}
	else {
		model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	unsigned int modelLoc = glGetUniformLocation(lightingShader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	//bind diffuse map
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);



	//render the cube
	glBindVertexArray(cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 18);

	//Active shader for the lamp 
	//also draw the lamp object
	glUseProgram(lampShader);

	//view and projection transformations
	projectionLoc = glGetUniformLocation(lampShader, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	viewLoc = glGetUniformLocation(lampShader, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	//world transformation
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
	modelLoc = glGetUniformLocation(lampShader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	//render the lamp
	glBindVertexArray(lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 18);

}

//function for loading a 2D texture from file
unsigned int loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data) {
		GLenum format = GL_RGB;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else {
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

int main()
{
	//glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Assignment 03:Q2 Shane", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
		//per-frame time logic
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//Input
		processInput(window);

		display();

		//glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Release used resources
	//Optional: de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);

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

	//Key controls object movement
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		rotFlg1 = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		rotFlg1 = false;
	}

	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		lightPosy += 0.002;
	}

	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
		lightPosy -= 0.002;
	}

	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
		lightPosz += 0.002;
	}

	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		lightPosz -= 0.002;
	}

	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		lightPosx += 0.002;
	}

	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		lightPosx -= 0.002;
	}

}

//glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//Make sure the viewport matches the new window dimensions; note that width and 
	//height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	//if (firstMouse)
	//{
	//	lastX = xpos;
	//	lastY = ypos;
	//	firstMouse = false;
	//}

	//float xoffset = xpos - lastX;
	//float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	//lastX = xpos;
	//lastY = ypos;

	//camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//camera.ProcessMouseScroll(yoffset);
}

