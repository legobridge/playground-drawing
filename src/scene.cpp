#include <iostream>
#include "glad/glad.h"
#include "scene.h"
#include "shape.h"

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
	
	cameraPos = glm::vec3(0.0f, 160.0f, 1100.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	// projection = glm::ortho(-WORLD_W / 2, WORLD_W / 2, -WORLD_H / 2, WORLD_H / 2, 0.1f, WORLD_D);
	projection = glm::perspective(glm::radians(45.0f), SCR_W / SCR_H, 0.1f, 2 * WORLD_D);

	srand(94558);
	colors.resize(30);
	for (size_t i = 0; i < colors.size(); i++)
	{
		colors[i].x = (rand() % 11) / 10.0f;
		colors[i].y = (rand() % 11) / 10.0f;
		colors[i].z = (rand() % 11) / 10.0f;
	}
	colors[0] = glm::vec3(0.000f, 0.000f, 0.800f);
	colors[5] = glm::vec3(0.000f, 0.650f, 0.002f);
	colors[6] = glm::vec3(0.115f, 0.115f, 0.115f);
	colors[7] = glm::vec3(0.900f, 0.700f, 0.000f);
	colors[8] = glm::vec3(0.900f, 0.000f, 0.000f);

	slideModel = new Model("../model/spiral-slide/spiral-slide.obj");

	pathSegments = new Path();

	vector<float> angles;
	angles.push_back(180.0f);
	angles.push_back(-90.0f);
	angles.push_back(-90.0f);
	angles.push_back(90.0f);
	angles.push_back(90.0f);

	for (size_t i = 0; i < 5; i++)
	{
		Bench* b = new Bench(angles[i]);
		benches.push_back(b);
	}

	ss = new SeeSaw();
}

// Destructor definition
Scene::~Scene()
{
	// Deallocation of Resources
	delete myShader;
	glDeleteVertexArrays(1, &VAO);
	delete slideModel;
	delete pathSegments;
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
void Scene::drawObject(Mesh mesh, glm::mat4 model, glm::vec3 colorVector)
{
	// model = glm::scale(model, glm::vec3(1.0f / 3000.0f, 1.0f / 3000.0f, 1.0f / 3000.0f));

	vector<Vertex> vertices = mesh.vertices;
	vector<unsigned int> indices = mesh.indices;
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
	glUniform3f(myColorLoc, colorVector.x, colorVector.y, colorVector.z);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Scene::drawPaths()
{
	glm::vec3 roadColor = glm::vec3(0.0f, 0.0f, 0.0f);

	for (size_t i = 0; i < pathSegments->meshes.size(); i++)
	{
		drawObject(pathSegments->meshes[i], pathSegments->models[i], roadColor);
	}
}

void Scene::drawBenches()
{
	glm::vec3 woodColor = glm::vec3(0.4f, 0.2f, 0.0f);
	glm::vec3 metalColor = glm::vec3(0.270f, 0.290f, 0.318f);
	vector<glm::vec3> worldPos;
	worldPos.push_back(glm::vec3(200.0f, 60.0f, 250.0f));
	worldPos.push_back(glm::vec3(1250.0f, 60.0f, 700.0f));
	worldPos.push_back(glm::vec3(1250.0f, 60.0f, -700.0f));
	worldPos.push_back(glm::vec3(-1250.0f, 60.0f, 700.0f));
	worldPos.push_back(glm::vec3(-1250.0f, 60.0f, -700.0f));

	for (size_t i = 0; i < benches.size(); i++)
	{
		for (size_t j = 0; j < benches[i]->meshesw.size(); j++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, worldPos[i]) * benches[i]->modelsw[j];
			drawObject(benches[i]->meshesw[j], model, woodColor);
		}
		for (size_t j = 0; j < benches[i]->meshesm.size(); j++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, worldPos[i]) * benches[i]->modelsm[j];
			drawObject(benches[i]->meshesm[j], model, metalColor);
		}
	}
}

void Scene::drawSeeSaws()
{
	glm::vec3 woodColor = glm::vec3(0.6f, 0.3f, 0.0f);
	glm::vec3 metalColor = glm::vec3(0.270f, 0.290f, 0.318f);
	glm::mat4 rot = glm::mat4(1.0f);
	rot = glm::rotate(rot, glm::radians(23.58f), glm::vec3(1.0f, 0.0f, 0.0f));
	float scaleBy = 1.3f;
	for (size_t j = 0; j < ss->meshesw.size(); j++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(scaleBy, scaleBy, scaleBy));
		model = glm::translate(model, glm::vec3(-150.0f, 40.0f, 250.0f)) * rot * ss->modelsw[j];
		drawObject(ss->meshesw[j], model, woodColor);
	}
	for (size_t j = 0; j < ss->meshesm.size(); j++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(scaleBy, scaleBy, scaleBy));
		model = glm::translate(model, glm::vec3(-150.0f, 40.0f, 250.0f)) * rot * ss->modelsm[j];
		drawObject(ss->meshesm[j], model, metalColor);
	}
	for (size_t j = 0; j < ss->meshes_base.size(); j++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(scaleBy, scaleBy, scaleBy));
		model = glm::translate(model, glm::vec3(-150.0f, 0.0f, 250.0f)) * ss->models_base[j];
		drawObject(ss->meshes_base[j], model, metalColor);
	}


	for (size_t j = 0; j < ss->meshesw.size(); j++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(scaleBy, scaleBy, scaleBy));
		model = glm::translate(model, glm::vec3(-50.0f, 40.0f, 250.0f)) * rot * ss->modelsw[j];
		drawObject(ss->meshesw[j], model, woodColor);
	}
	for (size_t j = 0; j < ss->meshesm.size(); j++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(scaleBy, scaleBy, scaleBy));
		model = glm::translate(model, glm::vec3(-50.0f, 40.0f, 250.0f)) * rot * ss->modelsm[j];
		drawObject(ss->meshesm[j], model, metalColor);
	}
	for (size_t j = 0; j < ss->meshes_base.size(); j++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(scaleBy, scaleBy, scaleBy));
		model = glm::translate(model, glm::vec3(-50.0f, 0.0f, 250.0f)) * ss->models_base[j];
		drawObject(ss->meshes_base[j], model, metalColor);
	}
}

// Call rendering function for all the pre-computed objects
void Scene::drawObjects()
{
	Mesh cuboidalMesh = shape::getCuboidalMesh(WORLD_W, 10.0f, WORLD_D);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -5.0f, 0.0f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	drawObject(cuboidalMesh, model, colors[25]);
	drawPaths();
	drawBenches();
	drawSeeSaws();
	for (unsigned int i = 0; i < slideModel->meshes.size(); i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-100.0f, 0.0f, -250.0f));
		model = glm::scale(model, glm::vec3(45.0f, 45.0f, 45.0f));
		drawObject(slideModel->meshes[i], model, colors[i]);
	}
}