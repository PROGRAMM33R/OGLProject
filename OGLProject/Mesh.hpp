#pragma once

#include "Std.hpp"

class Mesh {

public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	unsigned int VAO;

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	void Draw(GLuint ID);

private:
	unsigned int VBO, EBO;
	void setupMesh();

};