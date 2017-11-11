#include <iostream>
#include "model.h"

using namespace std;

Model::Model(char *path)
{
	loadModel(path);
}

void Model::loadModel(string path)
{
	Assimp::Importer import;
	const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
		return;
	}

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
	// Process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	// Then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		// Process vertex positions
		glm::vec3 v;
		v.x = mesh->mVertices[i].x;
		v.y = mesh->mVertices[i].y;
		v.z = mesh->mVertices[i].z;
		vertex.Position = v;
		v.x = mesh->mNormals[i].x;
		v.y = mesh->mNormals[i].y;
		v.z = mesh->mNormals[i].z;
		vertex.Normal = v;
		vertices.push_back(vertex);
	}

	// Process indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	/*for (size_t i = 0; i < indices.size(); i += 3)
	{
		glm::vec3 faceNormal = glm::normalize(glm::cross(vertices[indices[i + 1]].Position - vertices[indices[i]].Position, vertices[indices[i + 2]].Position - vertices[indices[i]].Position));
		vertices[indices[i]].Normal += faceNormal;
		vertices[indices[i + 1]].Normal += faceNormal;
		vertices[indices[i + 2]].Normal += faceNormal;
	}

	for (size_t i = 0; i < vertices.size(); i++)
	{
		vertices[i].Normal = glm::normalize(vertices[i].Normal);
	}*/

	return Mesh(vertices, indices);
}