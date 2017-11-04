#include "seesaw.h"
#include "shape.h"

using namespace std;

SeeSaw::SeeSaw(float angle)
{
	Mesh woodenSegment = shape::getCuboidalMesh(180.0f, 36.0f, 5.0f);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, -4.0f, -28.0f));
	meshesw.push_back(woodenSegment);
	modelsw.push_back(model);
}