#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "shader.h"
#include "mesh.h"

class Model
{
public:
	// Vector of meshes
	std::vector<Mesh> meshes;

	// Constructor
	Model(char *path);

private:
	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
};
#endif