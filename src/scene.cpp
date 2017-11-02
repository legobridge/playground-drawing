#include <iostream>
#include "glad/glad.h"
#include "scene.h"

using namespace std;

// Constructor definition
Scene::Scene()
{
	// Build and compile shaders
	myShader = new Shader("../src/shader/vertex.shader", "../src/shader/fragment.shader");

	// Use the compiled shader program
	myShader->use();

	// Generate and bind vertex array object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	pitch = 0.0f;
	yaw = -90.0f;
	roll = 0.0f;
	
	cameraPos = glm::vec3(0.0f, 10.0f, 30.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	// projection = glm::ortho(-WORLD_W / 2, WORLD_W / 2, -WORLD_H / 2, WORLD_H / 2, 0.1f, WORLD_D);
	projection = glm::perspective(glm::radians(45.0f), SCR_W / SCR_H, 0.1f, WORLD_D);

	myModel = new Model("../model/spiral-slide/spiral-slide.obj");
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
void Scene::drawObject(vector<Vertex> vertices, vector<unsigned int> indices, glm::mat4 model, vector<float> colorVector)
{
	unsigned int VBO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	unsigned int modelLoc = glGetUniformLocation(myShader->ID, "model");
	unsigned int viewLoc = glGetUniformLocation(myShader->ID, "view");
	unsigned int projectionLoc = glGetUniformLocation(myShader->ID, "projection");
	unsigned int myColorLoc = glGetUniformLocation(myShader->ID, "myColor");

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniform3f(myColorLoc, colorVector[0], colorVector[1], colorVector[2]);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

// Call rendering functions for all the pre-computed objects
void Scene::drawObjects()
{
	vector<vector<float>> colors(1);
	colors[0].resize(3);
	for (unsigned int i = 0; i < myModel->meshes.size(); i++)
	{
		colors[0][i % 3] = 1.0f;
		colors[0][(i + 1) % 3] = 0.0f;
		colors[0][(i + 2) % 3] = 0.0f;
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -30.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		drawObject(myModel->meshes[i].vertices, myModel->meshes[i].indices, model, colors[0]);
	}
}