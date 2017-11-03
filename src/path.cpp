#include "path.h"
#include "shape.h"

using namespace std;

Path::Path()
{
	Mesh roadSegment = shape::getCuboidalMesh(200.0f, 10.0f, 202.0f);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 900.0f));
	meshes.push_back(roadSegment);
	models.push_back(model);

	roadSegment = shape::getCuboidalMesh(2200.0f, 10.0f, 100.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 750.0f));
	meshes.push_back(roadSegment);
	models.push_back(model);

	roadSegment = shape::getCuboidalMesh(2000.0f, 10.0f, 100.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(100.0f, 0.0f, 650.0f));
	meshes.push_back(roadSegment);
	models.push_back(model);

	roadSegment = shape::getCuboidalMesh(100.0f, 10.0f, 300.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-850.0f, 0.0f, 450.0f));
	meshes.push_back(roadSegment);
	models.push_back(model);

	roadSegment = shape::getCuboidalMesh(100.0f, 10.0f, 500.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-450.0f, 0.0f, 350.0f));
	meshes.push_back(roadSegment);
	models.push_back(model);

	roadSegment = shape::getCuboidalMesh(100.0f, 10.0f, 200.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(1050.0f, 0.0f, 500.0f));
	meshes.push_back(roadSegment);
	models.push_back(model);

	roadSegment = shape::getCuboidalMesh(100.0f, 10.0f, 100.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(1150.0f, 0.0f, 450.0f));
	meshes.push_back(roadSegment);
	models.push_back(model);

	roadSegment = shape::getCuboidalMesh(100.0f, 10.0f, 1000.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(1250.0f, 0.0f, 0.0f));
	meshes.push_back(roadSegment);
	models.push_back(model);

	roadSegment = shape::getCuboidalMesh(900.0f, 10.0f, 100.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(750.0f, 0.0f, -250.0f));
	meshes.push_back(roadSegment);
	models.push_back(model);

	roadSegment = shape::getCuboidalMesh(100.0f, 10.0f, 800.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(350.0f, 0.0f, -400.0f));
	meshes.push_back(roadSegment);
	models.push_back(model);

	roadSegment = shape::getCuboidalMesh(1100.0f, 10.0f, 100.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-150.0f, 0.0f, 50.0f));
	meshes.push_back(roadSegment);
	models.push_back(model);

	roadSegment = shape::getCuboidalMesh(100.0f, 10.0f, 800.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-650.0f, 0.0f, -400.0f));
	meshes.push_back(roadSegment);
	models.push_back(model);

	roadSegment = shape::getCuboidalMesh(1100.0f, 10.0f, 100.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-150.0f, 0.0f, -850.0f));
	meshes.push_back(roadSegment);
	models.push_back(model);

	roadSegment = shape::getCuboidalMesh(500.0f, 10.0f, 100.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-950.0f, 0.0f, -250.0f));
	meshes.push_back(roadSegment);
	models.push_back(model);

	roadSegment = shape::getCuboidalMesh(100.0f, 10.0f, 1000.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1250.0f, 0.0f, 0.0f));
	meshes.push_back(roadSegment);
	models.push_back(model);
}