#include "roundabout.h"
#include "shape.h"

using namespace std;

Roundabout::Roundabout()
{
	// Base parameters
	meshb = shape::getCylindricalMesh(150.0f, 20.0f);
	modelb = glm::mat4(1.0f);
	modelb = glm::translate(modelb, glm::vec3(0.0f, 20.0f, 0.0f));

	// Central pole parameters
	meshp = shape::getCylindricalMesh(5.0f, 144.0f);
	modelp = glm::mat4(1.0f);
	modelp = glm::translate(modelp, glm::vec3(0.0f, 72.0f, 0.0f));

	// Handle bar parameters
	Mesh verticalHandleBar = shape::getCylindricalMesh(5.0f, 112.5f);
	Mesh horizontalHandleBar = shape::getCylindricalMesh(5.0f, 135.0f);

	for (int i = 0; i < 6; i++)
	{
		// Vertical bar
		meshesh.push_back(verticalHandleBar);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(135.0f * sin(glm::radians(60.0f * i)), 83.75f, 135.0f * cos(glm::radians(60.0f * i))));
		modelsh.push_back(model);

		// Horizontal bar
		meshesh.push_back(horizontalHandleBar);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(67.5f * sin(glm::radians(60.0f * i)), 135.0f, 67.5f * cos(glm::radians(60.0f * i))));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(sin(glm::radians(90.0f + 60.0f * i)), 0.0f, cos(glm::radians(90.0f + 60.0f * i))));
		modelsh.push_back(model);
	}
}