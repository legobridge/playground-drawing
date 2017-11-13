#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
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

	time = 0.0f;

	timescale = 16.0f;

	paused = true;

	cameraSpeed = 15.0f;

	pitch = 0.0f;
	yaw = -90.0f;
	roll = 0.0f;
	
	cameraPos = glm::vec3(0.0f, 160.0f, 1200.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	// projection = glm::ortho(-WORLD_W / 2, WORLD_W / 2, -WORLD_H / 2, WORLD_H / 2, 0.1f, WORLD_D);
	projection = glm::perspective(glm::radians(45.0f), SCR_W / SCR_H, 0.1f, 4 * WORLD_D);

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

	seeSaw = new SeeSaw();

	roundabout = new Roundabout();

	swing = new Swing();

	fenceModel = new Model("../model/fence/fence.obj");

	jungleGymModel = new Model("../model/jungle-gym/jungle-gym.obj");

	domeModel = new Model("../model/dome-jungle-gym/dome-jungle-gym.obj");

	slideModel = new Model("../model/spiral-slide/spiral-slide.obj");

	colors["red"] = glm::vec3(0.778f, 0.040f, 0.040f);
	colors["blue"] = glm::vec3(0.000f, 0.000f, 0.700f);
	colors["green"] = glm::vec3(0.065f, 0.350f, 0.065f);
	colors["yellow"] = glm::vec3(0.976f, 0.890f, 0.086f);
	colors["orange"] = glm::vec3(0.837f, 0.279f, 0.010f);
	colors["black"] = glm::vec3(0.010f, 0.010f, 0.010f);
	colors["white"] = glm::vec3(0.900f, 0.900f, 0.800f);
	colors["wood"] = glm::vec3(0.400f, 0.200f, 0.000f);
	colors["metal"] = glm::vec3(0.270f, 0.290f, 0.318f);
	colors["dirt"] = glm::vec3(0.308f, 0.100f, 0.053f);
	colors["grass"] = glm::vec3(0.100f, 0.600f, 0.100f);
	colors["rope"] = glm::vec3(0.398f, 0.337f, 0.220f);
}

// Destructor definition
Scene::~Scene()
{
	// Deallocation of Resources
	delete myShader;
	glDeleteVertexArrays(1, &VAO);
	delete pathSegments;
	for (size_t i = 0; i < benches.size(); i++)
	{
		delete benches[i];
	}
	delete seeSaw;
	delete roundabout;
	delete swing;
	delete fenceModel;
	delete domeModel;
	delete jungleGymModel;
	delete slideModel;
}

// Toggle time (on/off)
void Scene::toggleTime()
{
	paused = !paused;
}

// Slow down time
void Scene::slowDownTime()
{
	timescale = max(0.0f, timescale - 2.0f);
}

// Speed up time
void Scene::speedUpTime()
{
	timescale = min(100.0f, timescale + 2.0f);
}

// Change camera movement speed
void Scene::changeSpeed(float by)
{
	cameraSpeed = max(cameraSpeed + by, 0.0f);
}

// Move into the scene
void Scene::moveIn()
{
	cameraPos += cameraSpeed * cameraFront;
}

// Move out of the scene
void Scene::moveOut()
{
	cameraPos -= cameraSpeed * cameraFront;
}

// Strafe to the left
void Scene::strafeLeft()
{
	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

// Strafe to the right
void Scene::strafeRight()
{
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
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

// Draw object from arguments
void Scene::drawObject(Mesh mesh, glm::mat4 model, glm::vec3 colorVector)
{
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

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	unsigned int modelLoc = glGetUniformLocation(myShader->ID, "model");
	unsigned int viewLoc = glGetUniformLocation(myShader->ID, "view");
	unsigned int projectionLoc = glGetUniformLocation(myShader->ID, "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	float sunX = WORLD_W * 5.0f * sin(glm::radians(time));
	float sunY = WORLD_W * 5.0f * cos(glm::radians(time));
	glm::vec3 lightPos = glm::vec3(sunX, sunY, 0.0f);
	long long lightAngle = (((long long)(time)) % 360);
	float lightVal = 0.1f;
	if (lightAngle > 340 || lightAngle < 20)
	{
		lightVal = 1.0f;
	}
	else if (lightAngle < 110)
	{
		lightVal = max(0.1f, (110.0f - lightAngle) / 90.0f);
	}
	else if (lightAngle > 250)
	{
		lightVal = max(0.1f, (lightAngle - 270.0f) / 90.0f);
	}
	glm::vec3 lightColor = glm::vec3(lightVal, lightVal, lightVal);

	unsigned int lightPosLoc = glGetUniformLocation(myShader->ID, "lightPos");
	unsigned int viewPosLoc = glGetUniformLocation(myShader->ID, "viewPos");
	unsigned int lightColorLoc = glGetUniformLocation(myShader->ID, "lightColor");
	unsigned int objectColorLoc = glGetUniformLocation(myShader->ID, "objectColor");

	glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(viewPosLoc, cameraPos.x, cameraPos.y, cameraPos.z);
	glUniform3f(lightColorLoc, lightColor.x, lightColor.y, lightColor.z);
	glUniform3f(objectColorLoc, colorVector.x, colorVector.y, colorVector.z);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}


// Draw terrain elements
void Scene::drawTerrain()
{
	Mesh cuboidalMesh = shape::getCuboidalMesh(10 * WORLD_W, 6.0f, 10 * WORLD_D);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -10.0f, 0.0f));
	drawObject(cuboidalMesh, model, colors["dirt"]);

	cuboidalMesh = shape::getCuboidalMesh(WORLD_W, 10.0f, WORLD_D);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -5.0f, 0.0f));
	drawObject(cuboidalMesh, model, colors["grass"]);
}

// Draw the paths
void Scene::drawPaths()
{
	for (size_t i = 0; i < pathSegments->meshes.size(); i++)
	{
		drawObject(pathSegments->meshes[i], pathSegments->models[i], colors["black"]);
	}
}

// Draw the benches
void Scene::drawBenches()
{
	vector<glm::vec3> worldPos;
	worldPos.push_back(glm::vec3(200.0f, 0.0f, 250.0f));
	worldPos.push_back(glm::vec3(1250.0f, 0.0f, 700.0f));
	worldPos.push_back(glm::vec3(1250.0f, 0.0f, -700.0f));
	worldPos.push_back(glm::vec3(-1250.0f, 0.0f, 700.0f));
	worldPos.push_back(glm::vec3(-1250.0f, 0.0f, -700.0f));

	for (size_t i = 0; i < benches.size(); i++)
	{
		for (size_t j = 0; j < benches[i]->meshesw.size(); j++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, worldPos[i]) * benches[i]->modelsw[j];
			drawObject(benches[i]->meshesw[j], model, colors["wood"]);
		}
		for (size_t j = 0; j < benches[i]->meshesm.size(); j++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, worldPos[i]) * benches[i]->modelsm[j];
			drawObject(benches[i]->meshesm[j], model, colors["metal"]);
		}
	}
}

// Draw the see-saws
void Scene::drawSeeSaws()
{
	glm::mat4 rot = glm::mat4(1.0f);
	rot = glm::rotate(rot, glm::radians(23.58f), glm::vec3(1.0f, 0.0f, 0.0f));
	float scaleBy = 1.3f;

	// First see-saw
	for (size_t j = 0; j < seeSaw->meshesw.size(); j++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(scaleBy, scaleBy, scaleBy));
		model = glm::translate(model, glm::vec3(-150.0f, 40.0f, 250.0f)) * rot * seeSaw->modelsw[j];
		drawObject(seeSaw->meshesw[j], model, colors["wood"]);
	}
	for (size_t j = 0; j < seeSaw->meshesm.size(); j++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(scaleBy, scaleBy, scaleBy));
		model = glm::translate(model, glm::vec3(-150.0f, 40.0f, 250.0f)) * rot * seeSaw->modelsm[j];
		drawObject(seeSaw->meshesm[j], model, colors["metal"]);
	}
	for (size_t j = 0; j < seeSaw->meshes_base.size(); j++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(scaleBy, scaleBy, scaleBy));
		model = glm::translate(model, glm::vec3(-150.0f, 0.0f, 250.0f)) * seeSaw->models_base[j];
		drawObject(seeSaw->meshes_base[j], model, colors["metal"]);
	}

	// Second see-saw
	for (size_t j = 0; j < seeSaw->meshesw.size(); j++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(scaleBy, scaleBy, scaleBy));
		model = glm::translate(model, glm::vec3(-50.0f, 40.0f, 250.0f)) * rot * seeSaw->modelsw[j];
		drawObject(seeSaw->meshesw[j], model, colors["wood"]);
	}
	for (size_t j = 0; j < seeSaw->meshesm.size(); j++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(scaleBy, scaleBy, scaleBy));
		model = glm::translate(model, glm::vec3(-50.0f, 40.0f, 250.0f)) * rot * seeSaw->modelsm[j];
		drawObject(seeSaw->meshesm[j], model, colors["metal"]);
	}
	for (size_t j = 0; j < seeSaw->meshes_base.size(); j++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(scaleBy, scaleBy, scaleBy));
		model = glm::translate(model, glm::vec3(-50.0f, 0.0f, 250.0f)) * seeSaw->models_base[j];
		drawObject(seeSaw->meshes_base[j], model, colors["metal"]);
	}
}

// Draw the roundabout
void Scene::drawRoundabout()
{	
	// Draw the base
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(800.0f, 0.0f, -625.0f)) * roundabout->modelb;
	drawObject(roundabout->meshb, model, colors["orange"]);

	// Draw the central pole
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(800.0f, 0.0f, -625.0f)) * roundabout->modelp;
	drawObject(roundabout->meshp, model, colors["red"]);

	// Draw the handlebars
	for (size_t i = 0; i < roundabout->meshesh.size(); i++)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(800.0f, 0.0f, -625.0f)) * roundabout->modelsh[i];
		drawObject(roundabout->meshesh[i], model, colors["yellow"]);
	}
}

// Draw the swing
void Scene::drawSwing()
{
	// First see-saw
	for (size_t j = 0; j < swing->meshesw.size(); j++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(800.0f, 0.0f, 150.0f)) * swing->modelsw[j];
		drawObject(swing->meshesw[j], model, colors["wood"]);
	}
	for (size_t j = 0; j < swing->meshesm.size(); j++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(800.0f, 0.0f, 150.0f)) * swing->modelsm[j];
		drawObject(swing->meshesm[j], model, colors["green"]);
	}
	for (size_t j = 0; j < swing->meshes_rope.size(); j++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(800.0f, 0.0f, 150.0f)) * swing->models_rope[j];
		drawObject(swing->meshes_rope[j], model, colors["rope"]);
	}
}

// Draw the fence
void Scene::drawFence()
{
	for (unsigned int i = 0; i < fenceModel->meshes.size(); i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1500.0f, 0.0f, -1000.0f));
		model = glm::scale(model, glm::vec3(10.0f, 7.0f, 10.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		drawObject(fenceModel->meshes[i], model, colors["white"]);
	}
}

// Draw the jungle gym
void Scene::drawJungleGym()
{
	vector<glm::vec3> meshColors(jungleGymModel->meshes.size());
	meshColors[0] = colors["yellow"];
	meshColors[1] = colors["red"];
	meshColors[2] = colors["blue"];
	for (unsigned int i = 0; i < jungleGymModel->meshes.size(); i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1000.0f, 0.0f, -350.0f));
		model = glm::scale(model, glm::vec3(38.0f, 38.0f, 38.0f));
		drawObject(jungleGymModel->meshes[i], model, meshColors[i]);
	}
}

// Draw the dome jungle gym
void Scene::drawDome()
{
	vector<glm::vec3> meshColors(jungleGymModel->meshes.size());
	meshColors[0] = colors["blue"];
	meshColors[1] = colors["yellow"];
	for (unsigned int i = 0; i < domeModel->meshes.size(); i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-850.0f, 0.0f, 400.0f));
		model = glm::scale(model, glm::vec3(110.0f, 110.0f, 110.0f));
		drawObject(domeModel->meshes[i], model, meshColors[i]);
	}
}

// Draw the spiral slide
void Scene::drawSpiralSlide()
{
	vector<glm::vec3> meshColors(slideModel->meshes.size(), glm::vec3(0.0f, 0.0f, 0.0f));
	meshColors[0] = colors["green"];
	meshColors[1] = colors["metal"];
	meshColors[2] = colors["blue"];
	meshColors[3] = colors["yellow"];
	meshColors[4] = colors["red"];
	for (unsigned int i = 0; i < slideModel->meshes.size(); i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-100.0f, 0.0f, -250.0f));
		model = glm::scale(model, glm::vec3(45.0f, 45.0f, 45.0f));
		drawObject(slideModel->meshes[i], model, meshColors[i]);
	}
}

// Call rendering function for all the pre-computed objects
void Scene::drawObjects()
{
	drawTerrain();
	drawPaths();
	drawBenches();
	drawSeeSaws();
	drawRoundabout();
	drawSwing();
	drawFence();
	drawJungleGym();
	drawDome();
	drawSpiralSlide();
}