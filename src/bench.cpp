#include "bench.h"
#include "shape.h"

using namespace std;

Bench::Bench(float angle)
{
	Mesh woodenSegment = shape::getCuboidalMesh(200.0f, 10.0f, 20.0f);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, -5.0f, -35.0f));
	meshesw.push_back(woodenSegment);
	modelsw.push_back(model);

	woodenSegment = shape::getCuboidalMesh(200.0f, 10.0f, 20.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, -5.0f, -10.0f));
	meshesw.push_back(woodenSegment);
	modelsw.push_back(model);

	woodenSegment = shape::getCuboidalMesh(200.0f, 10.0f, 20.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, -5.0f, 15.0f));
	meshesw.push_back(woodenSegment);
	modelsw.push_back(model);

	woodenSegment = shape::getCuboidalMesh(200.0f, 10.0f, 20.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, -5.0f, 40.0f));
	meshesw.push_back(woodenSegment);
	modelsw.push_back(model);

	woodenSegment = shape::getCuboidalMesh(200.0f, 20.0f, 10.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, 20.0f, -40.0f));
	meshesw.push_back(woodenSegment);
	modelsw.push_back(model);

	woodenSegment = shape::getCuboidalMesh(200.0f, 20.0f, 10.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, 45.0f, -40.0f));
	meshesw.push_back(woodenSegment);
	modelsw.push_back(model);

	woodenSegment = shape::getCuboidalMesh(200.0f, 20.0f, 10.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, 70.0f, -40.0f));
	meshesw.push_back(woodenSegment);
	modelsw.push_back(model);

	Mesh metallicSegment = shape::getCylindricalMesh(5.0f, 90.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-75.0f, -15.0f, -5.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);

	metallicSegment = shape::getCylindricalMesh(5.0f, 90.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(75.0f, -15.0f, -5.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);

	metallicSegment = shape::getCylindricalMesh(5.0f, 160.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, -15.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);

	metallicSegment = shape::getCylindricalMesh(5.0f, 140.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-75.0f, 0.0f, -47.5f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);

	metallicSegment = shape::getCylindricalMesh(5.0f, 140.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(75.0f, 0.0f, -47.5f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);

	metallicSegment = shape::getCylindricalMesh(5.0f, 44.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-75.0f, -38.0f, 35.0f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);

	metallicSegment = shape::getCylindricalMesh(5.0f, 44.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(75.0f, -38.0f, 35.0f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);
}