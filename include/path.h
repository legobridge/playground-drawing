#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "mesh.h"

class Path
{
public:
	// Vectors of path segments
	std::vector<Mesh> meshes;
	std::vector<glm::mat4> models;

	// Constructor
	Path();
};