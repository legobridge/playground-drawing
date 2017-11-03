#include "bench.h"
#include "shape.h"

using namespace std;

Bench::Bench(float angle)
{
	Mesh woodenSegment = shape::getCuboidalMesh(160.0f, 8.0f, 16.0f);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, -4.0f, -28.0f));
	meshesw.push_back(woodenSegment);
	modelsw.push_back(model);

	woodenSegment = shape::getCuboidalMesh(160.0f, 8.0f, 16.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, -4.0f, -8.0f));
	meshesw.push_back(woodenSegment);
	modelsw.push_back(model);

	woodenSegment = shape::getCuboidalMesh(160.0f, 8.0f, 16.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, -4.0f, 12.0f));
	meshesw.push_back(woodenSegment);
	modelsw.push_back(model);

	woodenSegment = shape::getCuboidalMesh(160.0f, 8.0f, 16.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, -4.0f, 32.0f));
	meshesw.push_back(woodenSegment);
	modelsw.push_back(model);

	woodenSegment = shape::getCuboidalMesh(160.0f, 16.0f, 8.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, 16.0f, -32.0f));
	meshesw.push_back(woodenSegment);
	modelsw.push_back(model);

	woodenSegment = shape::getCuboidalMesh(160.0f, 16.0f, 8.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, 36.0f, -32.0f));
	meshesw.push_back(woodenSegment);
	modelsw.push_back(model);

	woodenSegment = shape::getCuboidalMesh(160.0f, 16.0f, 8.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, 56.0f, -32.0f));
	meshesw.push_back(woodenSegment);
	modelsw.push_back(model);

	Mesh metallicSegment = shape::getCylindricalMesh(4.0f, 70.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-60.0f, -12.0f, -3.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);

	metallicSegment = shape::getCylindricalMesh(4.0f, 70.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(60.0f, -12.0f, -3.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);

	metallicSegment = shape::getCylindricalMesh(4.0f, 128.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, -12.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);

	metallicSegment = shape::getCylindricalMesh(4.0f, 120.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-60.0f, 0.0f, -38.0f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);

	metallicSegment = shape::getCylindricalMesh(4.0f, 120.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(60.0f, 0.0f, -38.0f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);

	metallicSegment = shape::getCylindricalMesh(4.0f, 46.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-60.0f, -37.0f, 28.0f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);

	metallicSegment = shape::getCylindricalMesh(4.0f, 46.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(60.0f, -37.0f, 28.0f));
	meshesm.push_back(metallicSegment);
	modelsm.push_back(model);
}