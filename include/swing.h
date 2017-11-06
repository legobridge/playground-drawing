#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "mesh.h"

class Swing
{
public:
	// Wooden parts
	std::vector<Mesh> meshesw;
	std::vector<glm::mat4> modelsw;

	// Metallic parts
	std::vector<Mesh> meshesm;
	std::vector<glm::mat4> modelsm;

	// Rope
	std::vector<Mesh> meshes_rope;
	std::vector<glm::mat4> models_rope;

	Swing();
};