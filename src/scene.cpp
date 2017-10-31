#include "glad/glad.h"
#include "scene.h"

using namespace std;

// Constructor definition
Scene::Scene()
{

	SCR_W = 1366.0f;
	SCR_H = 768.0f;

	WORLD_W = 160.0f;
	WORLD_H = 90.0f;
	WORLD_D = 90.0f;

	// Build and compile shaders
	myShader = new Shader("../src/shader/vertex.shader", "../src/shader/fragment.shader");

	// Use the compiled shader program
	myShader -> use();

	// Generate and bind vertex array object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	deltaTime = 0.0f;
	lastFrame = 0.0f;

	pitch = 0.0f;
	yaw = -90.0f;
	roll = 0.0f;
	
	cameraPos = glm::vec3(0.0f, 0.0f, 30.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	// projection = glm::ortho(-WORLD_W / 2, WORLD_W / 2, -WORLD_H / 2, WORLD_H / 2, 0.1f, WORLD_D);
	projection = glm::perspective(glm::radians(45.0f), SCR_W / SCR_H, 0.1f, WORLD_D);
}

// Destructor definition
Scene::~Scene()
{
	// Deallocation of Resources
	delete myShader;
	glDeleteVertexArrays(1, &VAO);
}

// Move into the scene
void Scene::moveIn()
{
	cameraPos += CAMERA_SPEED * cameraFront;
}

// Move out of the scene
void Scene::moveOut()
{
	cameraPos -= CAMERA_SPEED * cameraFront;
}

// Strafe to the left
void Scene::strafeLeft()
{
	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * CAMERA_SPEED;
}

// Strafe to the right
void Scene::strafeRight()
{
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * CAMERA_SPEED;
}

// Pan the camera
void Scene::pan(float xoffset, float yoffset)
{
	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	if (yaw >= 360.0f)
		yaw -= 360.0f;
	if (yaw <= -360.0f)
		yaw += 360.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);
	cameraFront = front;
}

// Roll to the left
void Scene::rollLeft()
{

}

// Roll to the right
void Scene::rollRight()
{

}

// Draw object from arguments
void Scene::drawObject(vector<float> vertexVector, glm::mat4 model, vector<float> colorVector)
{
	float* v = new float[vertexVector.size()];
	for (size_t i = 0; i < vertexVector.size(); i++)
	{
		v[i] = vertexVector[i];
	}

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexVector.size(), v, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int modelLoc = glGetUniformLocation(myShader -> ID, "model");
	unsigned int viewLoc = glGetUniformLocation(myShader -> ID, "view");
	unsigned int projectionLoc = glGetUniformLocation(myShader->ID, "projection");
	unsigned int myColorLoc = glGetUniformLocation(myShader->ID, "myColor");

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniform3f(myColorLoc, colorVector[0], colorVector[1], colorVector[2]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDeleteBuffers(1, &VBO);
	delete [] v;
}

// Call rendering functions for all the pre-computed objects
void Scene::drawObjects()
{
	vector<float> vertices1 = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	vector<float> vertices2 = {
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f
	};
	vector<float> vertices3 = {

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f
	};

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(10.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
	vector<float> color1 = { 0.0f, 0.5f, 1.0f };
	vector<float> color2 = { 1.0f, 0.5f, 0.4f };
	vector<float> color3 = { 0.3f, 1.0f, 0.4f };
	drawObject(vertices1, model, color1);
	drawObject(vertices2, model, color2);
	drawObject(vertices3, model, color3);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
	drawObject(vertices1, model, color1);
	drawObject(vertices2, model, color2);
	drawObject(vertices3, model, color3);
}