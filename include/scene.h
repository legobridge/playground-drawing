#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "shader.h"
#include "model.h"
#include "path.h"
#include "bench.h"

class Scene
{
public:

	// Screen dimensions
	const float SCR_W = 1366.0f;
	const float SCR_H = 768.0f;

	// World dimensions
	const float WORLD_W = 3000.0f;
	const float WORLD_H = 1000.0f;
	const float WORLD_D = 2000.0f;

	// Pointer to a Shader object
	Shader* myShader;

	// The Vertex Array Object to draw from
	unsigned int VAO;

	// Base camera movement speed
	const float CAMERA_SPEED = 10.0f;

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

	// Model of slide (made in Blender)
	Model* slideModel;

	// Path object
	Path* pathSegments;

	// Vector of bench objects
	std::vector<Bench*> benches;

	// Vector of colors
	std::vector<glm::vec3> colors;

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

	// Draw an object using arguments
	void drawObject(Mesh mesh, glm::mat4 model, glm::vec3 colorVector);

	// Draw the paths
	void drawPaths();

	// Draw the benches
	void drawBenches();

	// Call rendering functions for all the pre-computed objects
	void drawObjects();
};

#endif