#include "seesaw.h"
#include "shape.h"

using namespace std;

SeeSaw::SeeSaw()
{
	Mesh woodenSegment = shape::getCuboidalMesh(36.0f, 5.0f, 180.0f);
	glm::mat4 model = glm::mat4(1.0f); 
	model = glm::translate(model, glm::vec3(0.0f, 2.5f, 0.0f));
	meshesw.push_back(woodenSegment);
	modelsw.push_back(model);

	Mesh metallicSegment = shape::getCylindricalMesh(1.5f, 10.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-12.0f, 10.0f, -60.0f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);
	
	metallicSegment = shape::getCylindricalMesh(1.5f, 10.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(12.0f, 10.0f, -60.0f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);

	metallicSegment = shape::getCylindricalMesh(1.5f, 27.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 15.0f, -60.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);

	metallicSegment = shape::getCylindricalMesh(1.5f, 10.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-12.0f, 10.0f, 60.0f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);

	metallicSegment = shape::getCylindricalMesh(1.5f, 10.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(12.0f, 10.0f, 60.0f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);

	metallicSegment = shape::getCylindricalMesh(1.5f, 27.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 15.0f, 60.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);

	metallicSegment = shape::getCuboidalMesh(5.0f, 44.0f, 5.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-18.5f, 22.0f, 0.0f));
	meshes_base.push_back(metallicSegment);
	models_base.push_back(model);

	metallicSegment = shape::getCuboidalMesh(5.0f, 44.0f, 5.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(18.5f, 22.0f, 0.0f));
	meshes_base.push_back(metallicSegment);
	models_base.push_back(model);
}