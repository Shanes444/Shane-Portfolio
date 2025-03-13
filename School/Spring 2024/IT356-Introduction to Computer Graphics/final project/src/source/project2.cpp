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
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 1000;

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
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

//timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//lighting
glm::vec3 lightPos;
float lightPosx, lightPosy, lightPosz;

unsigned int texture1;
unsigned int texture2;

//positions all containers
glm::vec3 cubePositions[] = {
	glm::vec3(0.0f, -5.0f, -1.5f),
	glm::vec3(1.0f,  5.0f, -2.0f),
	glm::vec3(2.0f,  1.0f, -3.0f),
	glm::vec3(3.0f, -1.0f, -1.0f),
	glm::vec3(4.0f,  0.0f, -2.5f),
	glm::vec3(5.0f,  3.0f, -3.5f),
	glm::vec3(-1.0f,-3.0f, -4.5f),
	glm::vec3(-2.0f, 2.0f, -5.5f),
	glm::vec3(-3.0f,-2.0f, -6.0f),
	glm::vec3(-4.0f, 4.0f, -5.0f),
	glm::vec3(-5.0f,-4.0f, -4.0f),
	glm::vec3(0.0f,0.0f, -8.0f),
	glm::vec3(0.0f,1.0f, -8.0f),
	glm::vec3(0.0f,2.0f, -8.0f),
	glm::vec3(0.0f,3.0f, -8.0f),
	glm::vec3(0.0f,4.0f, -8.0f),
	glm::vec3(0.0f,5.0f, -8.0f),
	glm::vec3(0.0f,6.0f, -8.0f),
	glm::vec3(0.0f,-1.0f, -8.0f),
	glm::vec3(0.0f,-2.0f, -8.0f),
	glm::vec3(0.0f,-3.0f, -8.0f),
	glm::vec3(0.0f,-4.0f, -8.0f),
	glm::vec3(0.0f,-5.0f, -8.0f),
	glm::vec3(0.0f,-6.0f, -8.0f)
};

bool rotFlg1;
bool rotFlg2;
bool mouseFlg = false;
bool colorFlg = false;
float angle;

void init(void)
{
	//configure global opengl state
	glEnable(GL_DEPTH_TEST);

	//Return shaderProgram, which is used to set the shader program's ID
	lightingShader = loadShader("../../src/shader/project2/light_casters2.vert", "../../src/shader/project2/light_casters2.frag");
	lampShader = loadShader("../../src/shader/project2/lamp2.vert", "../../src/shader/project2/lamp2.frag");

	//set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
		//positions           //normals            //texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
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
	//note that we update the lamp's position attribute's stride to reflect the updated buffer data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Load textures 
	texture1 = loadTexture("../../src/resources/textures/sephiroth.png");
	texture2 = loadTexture("../../src/resources/textures/cloud.png");

	glUseProgram(lightingShader);
	unsigned int materialDiffuseLoc = glGetUniformLocation(lightingShader, "material.texture1");
	glUniform1i(materialDiffuseLoc, 0);

	unsigned int materialSpecularLoc = glGetUniformLocation(lightingShader, "material.texture2");
	glUniform1i(materialSpecularLoc, 1);

	rotFlg1 = false;
	angle = 0.0f;

	lightPosx = 1.2f;
	lightPosy = 1.0f;
	lightPosz = 2.0f;
}

void display()
{
	//Render
	if(colorFlg == false)
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	else
		glClearColor(sin(glfwGetTime()/2)/2, sin(glfwGetTime()/4)/2, sin(glfwGetTime())/2, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // also clear the depth buffer now!

	lightPos = glm::vec3(lightPosx, lightPosy, lightPosz);

	//activate shader
	//be sure to activate shader when setting uniforms/drawing objects
	glUseProgram(lightingShader);

	unsigned int lightPosLoc = glGetUniformLocation(lightingShader, "light.position");
	glUniform3f(lightPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);

	unsigned int lightDirLoc = glGetUniformLocation(lightingShader, "light.direction");
	glUniform3f(lightDirLoc, camera.Front.x, camera.Front.y, camera.Front.z);

	unsigned int cutOffLoc = glGetUniformLocation(lightingShader, "light.cutOff");
	glUniform1f(cutOffLoc, glm::cos(glm::radians(12.5f)));

	unsigned int outerCutOffLoc = glGetUniformLocation(lightingShader, "light.outerCutOff");
	glUniform1f(outerCutOffLoc, glm::cos(glm::radians(17.5f)));
	   
	unsigned int cameraPosLoc = glGetUniformLocation(lightingShader, "viewPos");
	glUniform3f(cameraPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);

	//light properties
	unsigned int ambientColorLoc = glGetUniformLocation(lightingShader, "light.ambient");
	glUniform3f(ambientColorLoc, 0.1f, 0.1f, 0.1f);

	unsigned int diffuseColorLoc = glGetUniformLocation(lightingShader, "light.diffuse");
	//darken the light a bit to fit the scene
	glUniform3f(diffuseColorLoc, 0.8f, 0.8f, 0.8f);

	unsigned int specularColorLoc = glGetUniformLocation(lightingShader, "light.specular");
	glUniform3f(specularColorLoc, 1.0f, 1.0f, 1.0f);

	unsigned int constantLoc = glGetUniformLocation(lightingShader, "light.constant");
	glUniform1f(constantLoc, 1.0f);

	unsigned int linearLoc = glGetUniformLocation(lightingShader, "light.linear");
	glUniform1f(linearLoc, 0.007f);

	unsigned int quadraticLoc = glGetUniformLocation(lightingShader, "light.quadratic");
	glUniform1f(quadraticLoc, 0.0002f);

	//material properties
	//specular lighting doesn't have full effect on this object's material
	unsigned int materialShininessLoc = glGetUniformLocation(lightingShader, "material.shininess");
	glUniform1f(materialShininessLoc, 0.0001f);

	//view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();

	unsigned int projectionLoc = glGetUniformLocation(lightingShader, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	unsigned int viewLoc = glGetUniformLocation(lightingShader, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	//bind diffuse map
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	//bind specular map
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	//render containers
	glBindVertexArray(cubeVAO);

	for (unsigned int i = 0; i < 24; i++)
	{
		//calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle_pos = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle_pos), glm::vec3(1.0f, 0.3f, 0.5f));

		if (rotFlg1)
		{
			if (i % 2 == 1) {
				angle = (float)glfwGetTime() / 2.0;
				model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
			}
			else {
				angle = (float)glfwGetTime() / 2.0;
				model = glm::translate(model, glm::vec3(0.0f, 5*sin(glfwGetTime()), 0.0f));
			}
		}
		else {
			model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (rotFlg2)
		{
			if (i % 2 == 0) {
				angle = (float)glfwGetTime() / 2.0;
				model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
			}
			else {
				angle = (float)glfwGetTime() / 2.0;
				model = glm::translate(model, glm::vec3(0.0f, 5 * sin(glfwGetTime()), 0.0f));
			}
		}
		else {
			model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
		}

		unsigned int modelLoc = glGetUniformLocation(lightingShader, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);		
	}

	//render the cube
	glBindVertexArray(lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//glStencilMask(0xFF);
	//glEnable(GL_DEPTH_TEST);
}

//function for loading a 2D texture from file
unsigned int loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
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
	else
	{
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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "final_project2_Shane", NULL, NULL);
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
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		rotFlg2 = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		rotFlg2 = false;
	}

	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		mouseFlg = true;
	}
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
		mouseFlg = false;
	}
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		colorFlg = true;
	}
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		colorFlg = false;
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
	if (mouseFlg) {
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

		lastX = xpos;
		lastY = ypos;

		camera.ProcessMouseMovement(xoffset, yoffset);
	}
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}