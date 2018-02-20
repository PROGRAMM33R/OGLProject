
#include "Std.hpp"
#include "Mesh.hpp"
#include "Boids.hpp"
#include "Wall.hpp"

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, Config *cfg) {
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	this->cfg = cfg;
	setupMesh();
}

void Mesh::Draw(Shader *shader, int objType, Boids *Boidss, Wall *walls) {

	if (Boidss != NULL && objType == DRAW_TYPE_BOIDS) {

		glm::mat4 model;
		glm::vec3 position = glm::vec3(Boidss->location->vec.x, Boidss->location->vec.y, Boidss->location->vec.z);
		
		// First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
		model = glm::translate(model, position);  

		if (this->cfg->SCENE_TYPE == "2D") {
			model = glm::rotate(model, Boidss->angleY(Boidss->velocity), glm::vec3(0, 1, 0));
		}
		else {
			//model = glm::rotate(model, hovno, glm::vec3(0.1, 0, 0));
			//model = glm::rotate(model, Boidss->angleY(Boidss->velocity), glm::vec3(0, 1, 0));
			//model = glm::rotate(model, Boidss->angleZ(Boidss->velocity), glm::vec3(0, 0, 1));
		}
		
		model = glm::translate(model, glm::vec3(Boidss->size.x, Boidss->size.y, Boidss->size.z));
		model = glm::scale(model, glm::vec3(Boidss->size));

		shader->setFloat("transparent", 1.0);
		shader->setMat4("Model", model);
	}
	if (walls != NULL && this->cfg->SCENE_TYPE != "3D" && (objType == DRAW_TYPE_WALL || objType == DRAW_TYPE_EXIT || DRAW_TYPE_FLOOR)) {

		if (objType == DRAW_TYPE_WALL) { 

			glm::mat4 model;
			float size = 200;
			glm::vec3 position;

			if (walls->angle != 0) {
				position = glm::vec3(walls->location->vec.x - 180, (-(this->cfg->BOID_OBJ_SIZE) - 240) + walls->location->vec.y, walls->location->vec.z + 200);
			}
			else {
				position = glm::vec3(walls->location->vec.x - 180, (-(this->cfg->BOID_OBJ_SIZE) - 240) + walls->location->vec.y, walls->location->vec.z - 180);
			}
			model = glm::translate(model, position);
			model = glm::rotate(model, walls->angle, glm::vec3(0, 1, 0));
			model = glm::translate(model, glm::vec3(size, size, size));

			if (walls->meshSize != 0) {
				model = glm::scale(model, glm::vec3(walls->meshSize, size + 100, size));
			}
			else {
				model = glm::scale(model, glm::vec3(50, size + 100, size));
			}
			
			shader->setFloat("transparent", 0.9);
			shader->setMat4("Model", model);

		}

		if (objType == DRAW_TYPE_FLOOR) {

			glm::mat4 model;
			float sizeX = (float)walls->meshSizeZ / 4070.0;
			float sizeZ = (float)walls->meshSizeX / 4070.0;
			glm::vec3 position;
			
			position = glm::vec3(
				walls->location->vec.x + (walls->meshSizeZ / 2) + 20,
				((walls->floor + 1) * 570) - 30, 
				walls->location->vec.z + (walls->meshSizeX / 2) + 20
			);

			model = glm::translate(model, position);
			//model = glm::translate(model, glm::vec3(size, size, size + 1000));
			model = glm::scale(model, glm::vec3(sizeX, 1, sizeZ));
			shader->setMat4("Model", model);

		}

		if (objType == DRAW_TYPE_EXIT) {

			glm::mat4 model;
			float size = 20;
			glm::vec3 position;

			position = glm::vec3(walls->location->vec.x, 220, walls->location->vec.z);
			model = glm::translate(model, position);
			model = glm::rotate(model, walls->angle, glm::vec3(0, 1, 0));
			model = glm::translate(model, glm::vec3(size, size, size));
			model = glm::scale(model, glm::vec3(size, size + 250, size));
			shader->setFloat("transparent", 0.7);
			shader->setMat4("Model", model);

		}

	}

	if (objType == DRAW_TYPE_SURFACE){

		glm::mat4 model; 
		int size = cfg->BOID_CUBE_SIZE / 1300;
		glm::vec3 position;
		if (this->cfg->SCENE_TYPE == "3D") {
			position = glm::vec3(0, -(this->cfg->BOID_CUBE_SIZE / 2) - 100, 0);
		}
		else {
			position = glm::vec3(0, -(this->cfg->BOID_OBJ_SIZE) - 50, 0);
		}
		model = glm::translate(model, position);
		model = glm::translate(model, glm::vec3(size, size, size));
		model = glm::scale(model, glm::vec3(size));
		shader->setMat4("Model", model);

	}

	if (objType == DRAW_TYPE_SKY) {

		glm::mat4 model; int size = 190000;
		glm::vec3 position = glm::vec3(-190000, -182000, -180000);
		model = glm::translate(model, position);
		model = glm::translate(model, glm::vec3(size, size, size));
		model = glm::scale(model, glm::vec3(size));
		shader->setMat4("Model", model);

	}

	for (register unsigned int i = 0, len = textures.size(); i < len; ++i) {
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