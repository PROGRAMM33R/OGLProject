
#include "Std.hpp"
#include "Mesh.hpp"
#include "Boids.hpp"

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, Config *cfg) {
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	this->cfg = cfg;
	setupMesh();
}

void Mesh::Draw(Shader *shader, Boids *Boidss) {

	if (Boidss != NULL) {

		glm::mat4 model;
		glm::vec3 position = glm::vec3(Boidss->location->vec.x, Boidss->location->vec.y, Boidss->location->vec.z);
		
		// First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
		model = glm::translate(model, position);  
		model = glm::rotate(model, Boidss->angleX(Boidss->acceleration), glm::vec3(1, 0, 0));
		//model = glm::rotate(model, Boidss->angleY(Boidss->acceleration), glm::vec3(0, 1, 0));
		model = glm::rotate(model, Boidss->angleZ(Boidss->acceleration), glm::vec3(0, 1, 0));
		
		model = glm::translate(model, glm::vec3(-0.2f * Boidss->size.x, -0.2 * Boidss->size.y, -0.2f * Boidss->size.z));
		model = glm::scale(model, glm::vec3(Boidss->size));

		shader->setMat4("Model", model);
	}
	else { // surface
		glm::mat4 model;
		glm::vec3 position = glm::vec3(0, -(this->cfg->BOID_CUBE_SIZE / 2) - 100, 0);
		model = glm::translate(model, position);
		shader->setMat4("Model", model);
	}

	for (register unsigned int i = 0; i < textures.size(); i++) {
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