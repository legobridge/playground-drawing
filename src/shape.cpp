#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "shape.h"

using namespace std;

namespace shape
{
	Mesh getCuboidalMesh(float x, float y, float z)
	{
		vector<Vertex> vertices;

		float vX = x / 2;
		float vY = y / 2;
		float vZ = z / 2;

		Vertex vertex;
		glm::vec3 v;

		v.x = -vX;
		v.y = -vY;
		v.z = -vZ;
		vertex.Position = v;
		vertices.push_back(vertex);

		v.x = vX;
		v.y = -vY;
		v.z = -vZ;
		vertex.Position = v;
		vertices.push_back(vertex);

		v.x = vX;
		v.y = vY;
		v.z = -vZ;
		vertex.Position = v;
		vertices.push_back(vertex);

		v.x = -vX;
		v.y = vY;
		v.z = -vZ;
		vertex.Position = v;
		vertices.push_back(vertex);

		v.x = -vX;
		v.y = vY;
		v.z = vZ;
		vertex.Position = v;
		vertices.push_back(vertex);

		v.x = -vX;
		v.y = -vY;
		v.z = vZ;
		vertex.Position = v;
		vertices.push_back(vertex);

		v.x = vX;
		v.y = -vY;
		v.z = vZ;
		vertex.Position = v;
		vertices.push_back(vertex);

		v.x = vX;
		v.y = vY;
		v.z = vZ;
		vertex.Position = v;
		vertices.push_back(vertex);

		vector<unsigned int> indices;

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		indices.push_back(2);
		indices.push_back(0);
		indices.push_back(3);

		indices.push_back(3);
		indices.push_back(4);
		indices.push_back(7);

		indices.push_back(7);
		indices.push_back(3);
		indices.push_back(2);

		indices.push_back(2);
		indices.push_back(1);
		indices.push_back(6);

		indices.push_back(6);
		indices.push_back(2);
		indices.push_back(7);

		indices.push_back(7);
		indices.push_back(6);
		indices.push_back(5);

		indices.push_back(5);
		indices.push_back(7);
		indices.push_back(4);

		indices.push_back(4);
		indices.push_back(3);
		indices.push_back(0);

		indices.push_back(0);
		indices.push_back(4);
		indices.push_back(5);

		indices.push_back(5);
		indices.push_back(0);
		indices.push_back(1);

		indices.push_back(1);
		indices.push_back(6);
		indices.push_back(5);

		Mesh mesh(vertices, indices);
		return mesh;
	}

	Mesh getCylindricalMesh(float r, float h)
	{
		const float incr = 1.0f;
		const unsigned int points = (unsigned int)(360 / incr);
		vector<Vertex> vertices(1 + 1 + points + points);
		vector<unsigned int> indices;

		Vertex vertex;
		glm::vec3 v;

		v.x = 0.0f;
		v.y = h / 2;
		v.z = 0.0f;
		vertex.Position = v;
		vertices[0] = vertex;

		v.x = 0.0f;
		v.y = -h / 2;
		v.z = 0.0f;
		vertex.Position = v;
		vertices[1] = vertex;

		for (int i = 0; i < points; i++)
		{
			v.x = r * (float)sin(glm::radians(i * incr));
			v.y = h / 2;
			v.z = r * (float)cos(glm::radians(i * incr));
			vertex.Position = v;
			vertices[2 + i] = vertex;

			unsigned int first1 = 2 + i;
			unsigned int second1 = (2 + i + 1 < 2 + points) ? (2 + i + 1) : (2);
			indices.push_back(0);
			indices.push_back(first1);
			indices.push_back(second1);

			v.x = r * (float)sin(glm::radians(i * incr));
			v.y = -h / 2;
			v.z = r * (float)cos(glm::radians(i * incr));
			vertex.Position = v;
			vertices[2 + points + i] = vertex;

			unsigned int first2 = 2 + points + i;
			unsigned int second2 = (2 + points + i + 1 < 2 + points + points) ? (2 + points + i + 1) : (2 + points);
			indices.push_back(1);
			indices.push_back(first2);
			indices.push_back(second2);

			indices.push_back(first1);
			indices.push_back(first2);
			indices.push_back(second2);

			indices.push_back(first1);
			indices.push_back(second1);
			indices.push_back(second2);
		}

		Mesh mesh(vertices, indices);
		return mesh;
	}
}