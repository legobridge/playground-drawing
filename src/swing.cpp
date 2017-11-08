#include "swing.h"
#include "shape.h"

using namespace std;

Swing::Swing()
{
	// Seats
	Mesh woodenSegment = shape::getCuboidalMesh(70.0f, 5.0f, 30.0f);
	glm::mat4 model = glm::mat4(1.0f); 
	model = glm::translate(model, glm::vec3(-75.0f, 37.5f, 0.0f));
	meshesw.push_back(woodenSegment);
	modelsw.push_back(model);

	woodenSegment = shape::getCuboidalMesh(70.0f, 5.0f, 30.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(75.0f, 37.5f, 0.0f));
	meshesw.push_back(woodenSegment);
	modelsw.push_back(model);

	// Top metallic bar
	Mesh metallicSegment = shape::getCylindricalMesh(5.0f, 360.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 250.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);
	
	// Supports
	metallicSegment = shape::getCylindricalMesh(4.0f, 290.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(176.0f, 115.0f, -57.0f));
	model = glm::rotate(model, glm::radians(22.5f), glm::vec3(1.0f, 0.0f, 0.0f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);

	metallicSegment = shape::getCylindricalMesh(4.0f, 290.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-176.0f, 115.0f, -57.0f));
	model = glm::rotate(model, glm::radians(22.5f), glm::vec3(1.0f, 0.0f, 0.0f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);

	metallicSegment = shape::getCylindricalMesh(4.0f, 290.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(176.0f, 115.0f, 57.0f));
	model = glm::rotate(model, glm::radians(-22.5f), glm::vec3(1.0f, 0.0f, 0.0f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);

	metallicSegment = shape::getCylindricalMesh(4.0f, 290.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-176.0f, 115.0f, 57.0f));
	model = glm::rotate(model, glm::radians(-22.5f), glm::vec3(1.0f, 0.0f, 0.0f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);

	// Horizontal crossbars
	metallicSegment = shape::getCylindricalMesh(3.0f, 155.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-177.0f, 60.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);

	metallicSegment = shape::getCylindricalMesh(3.0f, 155.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(177.0f, 60.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);

	// Ropes
	Mesh ropeSegment = shape::getCylindricalMesh(1.0f, 217.5f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-105.0f, 146.25f, 0.0f));
	meshes_rope.push_back(ropeSegment);
	models_rope.push_back(model);

	ropeSegment = shape::getCylindricalMesh(1.0f, 217.5f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(105.0f, 146.25f, 0.0f));
	meshes_rope.push_back(ropeSegment);
	models_rope.push_back(model);

	ropeSegment = shape::getCylindricalMesh(1.0f, 217.5f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-45.0f, 146.25f, 0.0f));
	meshes_rope.push_back(ropeSegment);
	models_rope.push_back(model);

	ropeSegment = shape::getCylindricalMesh(1.0f, 217.5f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(45.0f, 146.25f, 0.0f));
	meshes_rope.push_back(ropeSegment);
	models_rope.push_back(model);
}