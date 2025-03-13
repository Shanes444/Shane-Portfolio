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
const unsigned int SCR_WIDTH = 1500;
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

glm::vec3 cubePts[12];
glm::vec3 normal[12];

//camera
Camera camera(glm::vec3(0.0f, 0.0f, 2.5f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

//timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//lighting
//glm::vec3 lightPos(1.2f, 0.2f, 2.0f);
glm::vec3 lightPos;
float lightPosx, lightPosy, lightPosz;

unsigned int diffuseMap;


unsigned int specularMap;


bool rotFlg1;
bool rotFlg2;
float angle;

void init(void)
{
	//configure global opengl state
	glEnable(GL_DEPTH_TEST);

	//Return shaderProgram, which is used to set the shader program's ID
	lightingShader = loadShader("../../src/shader/lighting_mapsQ4.vert", "../../src/shader/lighting_mapsQ4.frag");
	lampShader = loadShader("../../src/shader/lampQ4.vert", "../../src/shader/lampQ4.frag");
	float a = 0.866025f/2.0f;
	float b = 0.5f/2.0f;
	float c = 1.0f/2.0f;
	float d = 0.0f;
	float e = 0.5f;

	cubePts[0] = glm::vec3( a,  b, -e);
	cubePts[1] = glm::vec3( d,  c, -e);
	cubePts[2] = glm::vec3(-a,  b, -e);
	cubePts[3] = glm::vec3(-a, -b, -e);
	cubePts[4] = glm::vec3( d, -c, -e);
	cubePts[5] = glm::vec3( a, -b, -e);

	cubePts[6] =  glm::vec3(a,   b, e);
	cubePts[7] =  glm::vec3(d,   c, e);
	cubePts[8] =  glm::vec3(-a,  b, e);
	cubePts[9] =  glm::vec3(-a, -b, e);
	cubePts[10] = glm::vec3(d,  -c, e);
	cubePts[11] = glm::vec3(a,  -b, e);

	normal[0] = glm::normalize(glm::cross(cubePts[6] - cubePts[7], cubePts[0] - cubePts[6]));
	normal[1] = glm::normalize(glm::cross(cubePts[7] - cubePts[8], cubePts[1] - cubePts[7]));
	normal[2] = glm::normalize(glm::cross(cubePts[8] - cubePts[9], cubePts[2] - cubePts[8]));
	normal[3] = glm::normalize(glm::cross(cubePts[9] - cubePts[10], cubePts[3] - cubePts[9]));
	normal[4] = glm::normalize(glm::cross(cubePts[10] - cubePts[11], cubePts[4] - cubePts[10]));
	normal[5] = glm::normalize(glm::cross(cubePts[11] - cubePts[6], cubePts[5] - cubePts[11]));
	normal[6] = glm::normalize(glm::cross(cubePts[8] - cubePts[7], cubePts[9] - cubePts[8]));
	normal[7] = glm::normalize(glm::cross(cubePts[2] - cubePts[3], cubePts[1] - cubePts[2]));


	float vertices[] = {
		cubePts[0].x,  cubePts[0].y, cubePts[0].z, normal[0].x, normal[0].y, normal[0].z, 0.0f, 1.0f,
		cubePts[6].x,  cubePts[6].y, cubePts[6].z, normal[0].x, normal[0].y, normal[0].z, 1.0f, 1.0f,
		cubePts[7].x,  cubePts[7].y, cubePts[7].z, normal[0].x, normal[0].y, normal[0].z, 1.0f, 0.0f,
		cubePts[7].x,  cubePts[7].y, cubePts[7].z, normal[0].x, normal[0].y, normal[0].z, 1.0f, 0.0f,
		cubePts[1].x,  cubePts[1].y, cubePts[1].z, normal[0].x, normal[0].y, normal[0].z, 0.0f, 0.0f,
		cubePts[0].x,  cubePts[0].y, cubePts[0].z, normal[0].x, normal[0].y, normal[0].z, 0.0f, 1.0f,

		cubePts[7].x,  cubePts[7].y, cubePts[7].z, normal[1].x, normal[1].y, normal[1].z, 0.0f, 1.0f,
		cubePts[8].x,  cubePts[8].y, cubePts[8].z, normal[1].x, normal[1].y, normal[1].z, 1.0f, 1.0f,
		cubePts[2].x,  cubePts[2].y, cubePts[2].z, normal[1].x, normal[1].y, normal[1].z, 1.0f, 0.0f,
		cubePts[2].x,  cubePts[2].y, cubePts[2].z, normal[1].x, normal[1].y, normal[1].z, 1.0f, 0.0f,
		cubePts[1].x,  cubePts[1].y, cubePts[1].z, normal[1].x, normal[1].y, normal[1].z, 0.0f, 0.0f,
		cubePts[7].x,  cubePts[7].y, cubePts[7].z, normal[1].x, normal[1].y, normal[1].z, 0.0f, 1.0f,

		cubePts[8].x,  cubePts[8].y, cubePts[8].z, normal[2].x, normal[2].y, normal[2].z, 0.0f, 1.0f,
		cubePts[2].x,  cubePts[2].y, cubePts[2].z, normal[2].x, normal[2].y, normal[2].z, 1.0f, 1.0f,
		cubePts[3].x,  cubePts[3].y, cubePts[3].z, normal[2].x, normal[2].y, normal[2].z, 1.0f, 0.0f,
		cubePts[3].x,  cubePts[3].y, cubePts[3].z, normal[2].x, normal[2].y, normal[2].z, 1.0f, 0.0f,
		cubePts[9].x,  cubePts[9].y, cubePts[9].z, normal[2].x, normal[2].y, normal[2].z, 0.0f, 0.0f,
		cubePts[8].x,  cubePts[8].y, cubePts[8].z, normal[2].x, normal[2].y, normal[2].z, 0.0f, 1.0f,

		cubePts[3].x,  cubePts[3].y, cubePts[3].z, normal[3].x, normal[3].y, normal[3].z, 0.0f, 1.0f,
		cubePts[4].x,  cubePts[4].y, cubePts[4].z, normal[3].x, normal[3].y, normal[3].z, 1.0f, 1.0f,
		cubePts[10].x,  cubePts[10].y, cubePts[10].z, normal[3].x, normal[3].y, normal[3].z, 1.0f, 0.0f,
		cubePts[10].x,  cubePts[10].y, cubePts[10].z, normal[3].x, normal[3].y, normal[3].z, 1.0f, 0.0f,
		cubePts[9].x,  cubePts[9].y, cubePts[9].z, normal[3].x, normal[3].y, normal[3].z, 0.0f, 0.0f,
		cubePts[3].x,  cubePts[3].y, cubePts[3].z, normal[3].x, normal[3].y, normal[3].z, 0.0f, 1.0f,

		cubePts[4].x,  cubePts[4].y, cubePts[4].z, normal[4].x, normal[4].y, normal[4].z, 0.0f, 1.0f,
		cubePts[5].x,  cubePts[5].y, cubePts[5].z, normal[4].x, normal[4].y, normal[4].z, 1.0f, 1.0f,
		cubePts[11].x,  cubePts[11].y, cubePts[11].z, normal[4].x, normal[4].y, normal[4].z, 1.0f, 0.0f,
		cubePts[11].x,  cubePts[11].y, cubePts[11].z, normal[4].x, normal[4].y, normal[4].z, 1.0f, 0.0f,
		cubePts[10].x,  cubePts[10].y, cubePts[10].z, normal[4].x, normal[4].y, normal[4].z, 0.0f, 0.0f,
		cubePts[4].x,  cubePts[4].y, cubePts[4].z, normal[4].x, normal[4].y, normal[4].z, 0.0f, 1.0f,

		cubePts[5].x,  cubePts[5].y, cubePts[5].z, normal[5].x, normal[5].y, normal[5].z, 0.0f, 1.0f,
		cubePts[11].x,  cubePts[11].y, cubePts[11].z, normal[5].x, normal[5].y, normal[5].z, 1.0f, 1.0f,
		cubePts[6].x,  cubePts[6].y, cubePts[6].z, normal[5].x, normal[5].y, normal[5].z, 1.0f, 0.0f,
		cubePts[6].x,  cubePts[6].y, cubePts[6].z, normal[5].x, normal[5].y, normal[5].z, 1.0f, 0.0f,
		cubePts[0].x,  cubePts[0].y, cubePts[0].z, normal[5].x, normal[5].y, normal[5].z, 0.0f, 0.0f,
		cubePts[5].x,  cubePts[5].y, cubePts[5].z, normal[5].x, normal[5].y, normal[5].z, 0.0f, 1.0f,

		cubePts[7].x,  cubePts[7].y, cubePts[7].z, normal[6].x, normal[6].y, normal[6].z, 0.0f, 1.0f,
		cubePts[8].x,  cubePts[8].y, cubePts[8].z, normal[6].x, normal[6].y, normal[6].z, 1.0f, 1.0f,
		cubePts[9].x,  cubePts[9].y, cubePts[9].z, normal[6].x, normal[6].y, normal[6].z, 1.0f, 0.0f,
		cubePts[9].x,  cubePts[9].y, cubePts[9].z, normal[6].x, normal[6].y, normal[6].z, 1.0f, 0.0f,
		cubePts[7].x,  cubePts[7].y, cubePts[7].z, normal[6].x, normal[6].y, normal[6].z, 0.0f, 0.0f,
		cubePts[6].x,  cubePts[6].y, cubePts[6].z, normal[6].x, normal[6].y, normal[6].z, 0.0f, 1.0f,
		cubePts[6].x,  cubePts[6].y, cubePts[6].z, normal[6].x, normal[6].y, normal[6].z, 0.0f, 1.0f,
		cubePts[9].x,  cubePts[9].y, cubePts[9].z, normal[6].x, normal[6].y, normal[6].z, 1.0f, 1.0f,
		cubePts[10].x,  cubePts[10].y, cubePts[10].z, normal[6].x, normal[6].y, normal[6].z, 1.0f, 0.0f,
		cubePts[10].x,  cubePts[10].y, cubePts[10].z, normal[6].x, normal[6].y, normal[6].z, 1.0f, 0.0f,
		cubePts[6].x,  cubePts[6].y, cubePts[6].z, normal[6].x, normal[6].y, normal[6].z, 0.0f, 0.0f,
		cubePts[11].x,  cubePts[11].y, cubePts[11].z, normal[6].x, normal[6].y, normal[6].z, 0.0f, 1.0f,

		cubePts[1].x,  cubePts[1].y, cubePts[1].z, normal[7].x, normal[7].y, normal[7].z, 0.0f, 1.0f,
		cubePts[2].x,  cubePts[2].y, cubePts[2].z, normal[7].x, normal[7].y, normal[7].z, 1.0f, 1.0f,
		cubePts[3].x,  cubePts[3].y, cubePts[3].z, normal[7].x, normal[7].y, normal[7].z, 1.0f, 0.0f,
		cubePts[3].x,  cubePts[3].y, cubePts[3].z, normal[7].x, normal[7].y, normal[7].z, 1.0f, 0.0f,
		cubePts[1].x,  cubePts[1].y, cubePts[1].z, normal[7].x, normal[7].y, normal[7].z, 0.0f, 0.0f,
		cubePts[0].x,  cubePts[0].y, cubePts[0].z, normal[7].x, normal[7].y, normal[7].z, 0.0f, 1.0f,
		cubePts[0].x,  cubePts[0].y, cubePts[0].z, normal[7].x, normal[7].y, normal[7].z, 0.0f, 1.0f,
		cubePts[3].x,  cubePts[3].y, cubePts[3].z, normal[7].x, normal[7].y, normal[7].z, 1.0f, 1.0f,
		cubePts[4].x,  cubePts[4].y, cubePts[4].z, normal[7].x, normal[7].y, normal[7].z, 1.0f, 0.0f,
		cubePts[4].x,  cubePts[4].y, cubePts[4].z, normal[7].x, normal[7].y, normal[7].z, 1.0f, 0.0f,
		cubePts[0].x,  cubePts[0].y, cubePts[0].z, normal[7].x, normal[7].y, normal[7].z, 0.0f, 0.0f,
		cubePts[5].x,  cubePts[5].y, cubePts[5].z, normal[7].x, normal[7].y, normal[7].z, 0.0f, 1.0f,

	};

	//First, configure the cube's VAO (and VBO)
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

	//Second, configure the light's VAO (VBO stays the same; 
	//the vertices are the same for the light object which is also a 3D cube)
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//note that we update the lamp's position attribute's stride to reflect the updated buffer data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Load textures 
	diffuseMap = loadTexture("../../src/resources/textures/wood1.png");
	
	glUseProgram(lightingShader);
	unsigned int materialDiffuseLoc = glGetUniformLocation(lightingShader, "material.diffuse");
	glUniform1i(materialDiffuseLoc, 0);

	//////////////////////////////////////////////////////////////////////////////////////////////////
	////Load texture for specular map
	//specularMap = loadTexture("../../src/resources/textures/container2_specular.png");
	specularMap = loadTexture("../../src/resources/textures/wood2.png");

	//Load material specular
	unsigned int materialSpecularLoc = glGetUniformLocation(lightingShader, "material.specular");
	glUniform1i(materialSpecularLoc, 1);

	//////////////////////////////////////////////////////////////////////////////////////////////////

	lightPosx = 1.2f;
	lightPosy = 0.2f;
	lightPosz = 0.6f;

	rotFlg1 = false;
	rotFlg2 = false;
	angle = 0.0f;
}

void display()
{
	//Render
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

	lightPos = glm::vec3(lightPosx, lightPosy, lightPosz);

	//activate shader
	//be sure to activate shader when setting uniforms/drawing objects
	glUseProgram(lightingShader);

	unsigned int lightPosLoc = glGetUniformLocation(lightingShader, "light.position");
	glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);

	unsigned int cameraPosLoc = glGetUniformLocation(lightingShader, "viewPos");
	glUniform3f(cameraPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);

	//light properties
	unsigned int ambientColorLoc = glGetUniformLocation(lightingShader, "light.ambient");
	glUniform3f(ambientColorLoc, 0.15f, 0.15f, 0.15f);

	unsigned int diffuseColorLoc = glGetUniformLocation(lightingShader, "light.diffuse");
	//darken the light a bit to fit the scene
	glUniform3f(diffuseColorLoc, 0.9f, 0.9f, 0.9);

	unsigned int specularColorLoc = glGetUniformLocation(lightingShader, "light.specular");
	glUniform3f(specularColorLoc, 1.0f, 1.0f, 1.0f);
	
	//material properties
	//specular lighting doesn't have full effect on this object's material
	unsigned int materialSpecularLoc = glGetUniformLocation(lightingShader, "material.specular");
	glUniform3f(materialSpecularLoc, 1.0f, 1.0f, 1.0f);

	unsigned int materialShininessLoc = glGetUniformLocation(lightingShader, "material.shininess");
	glUniform1f(materialShininessLoc, 32.0f);

	//view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();

	unsigned int projectionLoc = glGetUniformLocation(lightingShader, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	unsigned int viewLoc = glGetUniformLocation(lightingShader, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	//world transformation
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	//model = glm::scale(model1, glm::vec3(1.0f));
	if (rotFlg1)
	{
		angle = -(float)glfwGetTime()/3.0;
		model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	}
	else if (rotFlg2)
	{
		angle = -(float)glfwGetTime() / 3.0;
		model = glm::rotate(model, angle, glm::vec3(1.0f, 0.0f, 0.0f));
	}
	else{
		model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	}

	unsigned int modelLoc = glGetUniformLocation(lightingShader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	//bind diffuse map
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);

	////////////////////////////////////////////////
	////bind specular map
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularMap);

	////////////////////////////////////////////////
	// 
	//render the cube
	glBindVertexArray(cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 60);

	//also draw the lamp object
	glUseProgram(lampShader);
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

	//render the cube
	glBindVertexArray(lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 60);
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
		GLenum format = GL_RED;
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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Assignment 03:Q4 Shane", NULL, NULL);
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

	//Keyboard controls
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		lightPosy += 0.02;
	}
	else if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
		lightPosy -= 0.02;
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		rotFlg1 = true;
		rotFlg2 = false;
	}
	else if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		rotFlg1 = false;
		rotFlg2 = false;
	}
	else if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		rotFlg2 = true;
		rotFlg1 = false;
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
	camera.ProcessMouseScroll(yoffset);
}