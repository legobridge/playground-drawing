#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "mesh.h"

class Roundabout
{
public:
	// Base
	Mesh meshb;
	glm::mat4 modelb;

	// Handles
	std::vector<Mesh> meshesh;
	std::vector<glm::mat4> modelsh;

	// Central pole
	Mesh meshp;
	glm::mat4 modelp;

	// Constructor
	Roundabout();
};