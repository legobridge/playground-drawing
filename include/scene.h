#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <map>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "shader.h"
#include "model.h"
#include "path.h"
#include "bench.h"
#include "seesaw.h"
#include "roundabout.h"
#include "swing.h"

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

	// In-Program time
	float time;

	// Timescale measure for day-night cycle
	float timescale;

	// Time pause state
	bool paused;

	// Base camera movement speed
	float cameraSpeed;

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

	// Path object
	Path* pathSegments;

	// Vector of bench objects
	std::vector<Bench*> benches;

	// See-saw object
	SeeSaw* seeSaw;

	// Roundabout object
	Roundabout* roundabout;

	// Swing object
	Swing* swing;

	// Fence model (made in Blender)
	Model* fenceModel;

	// Jungle gym model (made in Blender)
	Model* jungleGymModel;

	// Dome jungle gym model (made in Blender)
	Model* domeModel;

	// Slide model (made in Blender)
	Model* slideModel;

	// Color map
	std::map<std::string, glm::vec3> colors;

	// Constructor
	Scene();

	// Destructor
	~Scene();

	// Toggle time (on/off)
	void toggleTime();

	// Slow down time
	void slowDownTime();

	// Speed up time
	void speedUpTime();

	// Change camera movement speed
	void changeSpeed(float by);

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

	// Draw an object using arguments
	void drawObject(Mesh mesh, glm::mat4 model, glm::vec3 colorVector);

	// Draw the ground
	void drawTerrain();

	// Draw the paths
	void drawPaths();

	// Draw the benches
	void drawBenches();

	// Draw the see-saws
	void drawSeeSaws();

	// Draw the roundabout
	void drawRoundabout();

	// Draw the swing
	void drawSwing();

	// Draw the fence
	void drawFence();

	// Draw the jungle gym
	void drawJungleGym();

	// Draw the dome jungle gym
	void drawDome();

	// Draw the spiral slide
	void drawSpiralSlide();

	// Call rendering functions for all the pre-computed objects
	void drawObjects();
};

#endif