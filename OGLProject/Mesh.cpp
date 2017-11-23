
#include "Std.hpp"
#include "Mesh.hpp"
#include "Boids.hpp"

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures) {
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	setupMesh();
}

void Mesh::Draw(Shader *shader, Boids *Boids) {
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;

	if (Boids != NULL) {

		float directionLine[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f,  0.5f, 0.0f
		};

		glm::mat4 model;
		glm::vec3 position = glm::vec3(Boids->location->vec.x, 1, Boids->location->vec.y);
		GLfloat direction = Boids->angle(Boids->location);
		
		model = glm::translate(model, position);  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
		//model = glm::translate(model, glm::vec3(0.2f * Boids->size.x, 0.2f * Boids->size.y, 0.0f)); // Move origin of rotation to center of quad
		model = glm::translate(model, glm::vec3(0.2f * Boids->size.x, 3.0f, 0.2f * Boids->size.y));
		//model = glm::rotate(model, direction, glm::vec3(0.0f, 3.0f, 0.0f)); // Then rotate
		//model = glm::translate(model, glm::vec3(-0.2f * Boids->size.x, -0.2f * Boids->size.y, 0.0f)); // Move origin back
		model = glm::translate(model, glm::vec3(-0.2f * Boids->size.x, 3.0f, -0.2f * Boids->size.y));
		model = glm::scale(model, glm::vec3(Boids->size, Boids->size.y)); // Last scale

		shader->setMat4("Model", model);
	}

	for (unsigned int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i); 
										 
		stringstream ss;
		string number;
		string name = textures[i].type;
		if (name == "material.diffuse")
			ss << diffuseNr++; 
		else if (name == "material.specular")
			ss << specularNr++;
		else if (name == "material.normal")
			ss << normalNr++;
		else if (name == "material.height")
			ss << heightNr++;
		number = ss.str();
		glUniform1i(glGetUniformLocation(shader->ID, (name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

	glBindVertexArray(0);
}