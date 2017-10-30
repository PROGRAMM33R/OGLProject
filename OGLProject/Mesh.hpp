#pragma once

#include "Std.hpp"
#include "Shader.hpp"

class Actor;
class Mesh {

public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	unsigned int VAO;

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	void Draw(Shader *shader, Actor *actor);

private:
	unsigned int VBO, EBO;
	void setupMesh();

};