#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "shader.h"
#include "model.h"

class Scene
{
public:

	// Screen dimensions
	const float SCR_W = 1366.0f;
	const float SCR_H = 768.0f;

	// World dimensions
	const float WORLD_W = 160.0f;
	const float WORLD_H = 90.0f;
	const float WORLD_D = 200.0f;

	// Pointer to a Shader object
	Shader* myShader;

	// The Vertex Array Object to draw from
	unsigned int VAO;

	// Base camera movement speed
	const float CAMERA_SPEED = 1.5f;

	// Euler angles
	float pitch;
	float yaw;
	float roll;

	// Camera properties
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	// View matrix
	glm::mat4 view;

	// Projection matrix
	glm::mat4 projection;

	// Model
	Model* myModel;

	// Constructor
	Scene();

	// Destructor
	~Scene();

	// Move into the scene
	void moveIn();

	// Move out of the scene
	void moveOut();

	// Strafe to the left
	void strafeLeft();

	// Strafe to the right
	void strafeRight();
	
	// Pan the camera
	void pan(float xoffset, float yoffset);

	// Roll to the left
	void rollLeft();

	// Roll to the right
	void rollRight();

	void drawObject(std::vector<Vertex> vertices, std::vector<unsigned int> indices, glm::mat4 model, std::vector<float> colorVector);

	// Call rendering functions for all the pre-computed objects
	void drawObjects();
};

#endif