#pragma once

#include "Std.hpp"
#include "Shader.hpp"

class Boids;
class Wall;
class Mesh {

public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	unsigned int VAO;

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, Config *cfg);
	void Draw(Shader *shader, int objType, Boids *Boids, Wall *walls);

private:
	Config *cfg;
	unsigned int VBO, EBO;
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	void setupMesh();

};