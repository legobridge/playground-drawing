#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "shader.h"

class Scene
{
public:

	// Screen dimensions
	float SCR_W;
	float SCR_H;

	// World dimensions
	float WORLD_W;
	float WORLD_H;
	float WORLD_D;

	// Pointer to a Shader object
	Shader* myShader;

	// The Vertex Array Object to draw from
	unsigned int VAO;

	// Base camera movement speed
	const float CAMERA_SPEED = 1.5f;

	// Time between frames
	float lastFrame;
	float deltaTime;

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

	void drawObject(std::vector<float> vertexVector, glm::mat4 model, std::vector<float> colorVector);

	// Call rendering functions for all the pre-computed objects
	void drawObjects();
};

#endif