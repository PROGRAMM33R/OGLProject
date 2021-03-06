
#include "Std.hpp"
#include "Mesh.hpp"
#include "Boids.hpp"
#include "Wall.hpp"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, Config *cfg) {
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	this->cfg = cfg;
	setupMesh();
}

void Mesh::Draw(InstanceStorage *instanceStorage) {

	if (instanceStorage->Boidss != NULL && (instanceStorage->objType == DRAW_TYPE_BOIDS || instanceStorage->objType == DRAW_TYPE_PREDATOR)) {

		glm::mat4 model;
		mat4 rotationMatrix;
		glm::vec3 position = glm::vec3(
			instanceStorage->Boidss->location->vec.x, 
			instanceStorage->Boidss->location->vec.y, 
			instanceStorage->Boidss->location->vec.z
		);
		
		// First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
		model = glm::translate(model, position);  

		if (this->cfg->SCENE_TYPE == "2D") {
			model = glm::rotate(model, instanceStorage->Boidss->angleY(instanceStorage->Boidss->velocity), glm::vec3(0, 1, 0));
		}
		else {
			
			//model = glm::rotate(model, instanceStorage->Boidss->angleX(instanceStorage->Boidss->velocity), glm::vec3(1, 0, 0));
			//model = glm::rotate(model,  (instanceStorage->Boidss->angleFi(instanceStorage->Boidss->velocity)) + ((float)3.14 / (float)2) * -1 , glm::vec3(0, 1, 0));
			//model = glm::rotate(model, instanceStorage->Boidss->angleZ(instanceStorage->Boidss->velocity), glm::vec3(0, 0, 1));

			float result = instanceStorage->Boidss->angleY(instanceStorage->Boidss->velocity);
			if (result > 0)
				model = glm::rotate(model, result - (float)1.75, glm::vec3(0, 1, 0));

			model = glm::rotate(model, instanceStorage->Boidss->angleZ(instanceStorage->Boidss->velocity), glm::vec3(0, 0, 1));
			//cout << instanceStorage->Boidss->angleY(instanceStorage->Boidss->velocity) << endl;
			
		}

		model = glm::translate(
			model, 
			glm::vec3(
				instanceStorage->Boidss->size.x, 
				instanceStorage->Boidss->size.y, 
				instanceStorage->Boidss->size.z
			)
		);
		model = glm::scale(model, glm::vec3(instanceStorage->Boidss->size));

		this->setTransparency(instanceStorage);
		instanceStorage->shader->setMat4("Model", model);
	}
	if (instanceStorage->walls != NULL && 
		this->cfg->SCENE_TYPE != "3D" && 
		(
			instanceStorage->objType == DRAW_TYPE_WALL || 
			instanceStorage->objType == DRAW_TYPE_EXIT || 
			instanceStorage->objType == DRAW_TYPE_FLOOR
		)) {

		if (instanceStorage->objType == DRAW_TYPE_WALL) {

			glm::mat4 model;
			float size = 200;
			glm::vec3 position;

			if (instanceStorage->walls->angle != 0) {
				position = glm::vec3(
					instanceStorage->walls->location->vec.x - 180, 
					(-(this->cfg->BOID_OBJ_SIZE) - 240) + instanceStorage->walls->location->vec.y, 
					instanceStorage->walls->location->vec.z + 200
				);
			}
			else {
				position = glm::vec3(
					instanceStorage->walls->location->vec.x - 180, 
					(-(this->cfg->BOID_OBJ_SIZE) - 240) + instanceStorage->walls->location->vec.y, 
					instanceStorage->walls->location->vec.z - 180
				);
			}
			model = glm::translate(model, position);
			model = glm::rotate(model, instanceStorage->walls->angle, glm::vec3(0, 1, 0));
			model = glm::translate(model, glm::vec3(size, size, size));

			if (instanceStorage->walls->meshSize != 0) {
				model = glm::scale(model, glm::vec3(instanceStorage->walls->meshSize, size + 100, size));
			}
			else {
				model = glm::scale(model, glm::vec3(46, size + 100, size));
			}

			this->setTransparency(instanceStorage);

			instanceStorage->shader->setMat4("Model", model);

		}

		if (instanceStorage->objType == DRAW_TYPE_FLOOR) {

			glm::mat4 model;
			float sizeX = (float)instanceStorage->walls->meshSizeZ / 4070.0;
			float sizeZ = (float)instanceStorage->walls->meshSizeX / 4070.0;
			glm::vec3 position;
			
			position = glm::vec3(
				instanceStorage->walls->location->vec.x + (instanceStorage->walls->meshSizeZ / 2) + 20,
				instanceStorage->walls->location->vec.y - 20,
				instanceStorage->walls->location->vec.z + (instanceStorage->walls->meshSizeX / 2) + 20
			);

			model = glm::translate(model, position);
			//model = glm::translate(model, glm::vec3(size, size, size + 1000));
			model = glm::scale(model, glm::vec3(sizeX, 1, sizeZ));

			this->setTransparency(instanceStorage);

			instanceStorage->shader->setMat4("Model", model);

		}

		if (instanceStorage->objType == DRAW_TYPE_EXIT) {

			glm::mat4 model;
			float size = 20;
			glm::vec3 position;

			position = glm::vec3(
				instanceStorage->walls->location->vec.x, 
				instanceStorage->walls->location->vec.y + 220, 
				instanceStorage->walls->location->vec.z
			);
			model = glm::translate(model, position);
			model = glm::rotate(model, instanceStorage->walls->angle, glm::vec3(0, 1, 0));
			model = glm::translate(model, glm::vec3(size, size, size));
			model = glm::scale(model, glm::vec3(size, size + 250, size));

			this->setTransparency(instanceStorage);

			instanceStorage->shader->setMat4("Model", model);

		}

	}

	if (instanceStorage->objType == DRAW_TYPE_LANDSCAPE){

		glm::mat4 model; 
		int size = 500;
		glm::vec3 position;

		if (this->cfg->SCENE_TYPE == "3D") {
			position = glm::vec3(0, -(this->cfg->BOID_CUBE_SIZE / 2) - cfg->BOID_CUBE_SIZE - 2800, 0);
		}
		else {
			position = glm::vec3(0, -550, 0);
		}

		model = glm::translate(model, position);
		model = glm::translate(model, glm::vec3(size, size, size));
		model = glm::scale(model, glm::vec3(size));
		this->setTransparency(instanceStorage);
		instanceStorage->shader->setMat4("Model", model);

	}

	if (instanceStorage->objType == DRAW_TYPE_SKY) {

		glm::mat4 model; int size = 20000;
		glm::vec3 position;
		
		if (this->cfg->SCENE_TYPE == "3D") {
			position = glm::vec3(instanceStorage->cameraX, instanceStorage->cameraY - 50000, instanceStorage->cameraZ);
		}
		else {
			position = glm::vec3(instanceStorage->cameraX, instanceStorage->cameraY - 27000, instanceStorage->cameraZ);
		}
		
		model = glm::translate(model, position);
		model = glm::translate(model, glm::vec3(size, size, size));
		model = glm::scale(model, glm::vec3(size));

		this->setTransparency(instanceStorage);
		instanceStorage->shader->setMat4("Model", model);

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
		glUniform1i(glGetUniformLocation(instanceStorage->shader->ID, (name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh(void) {
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

void Mesh::setTransparency(InstanceStorage *instanceStorage) {

	if (instanceStorage->walls != NULL) {
		if (!instanceStorage->isExitPath) {

			if ((instanceStorage->walls->floor == instanceStorage->activeFloor) && instanceStorage->activeFloor != 98) {
				instanceStorage->shader->setFloat("transparent", 1.0);
			}
			else if (instanceStorage->activeFloor == 99) {
				instanceStorage->shader->setFloat("transparent", 1.0);
			}
			else {
				instanceStorage->shader->setFloat("transparent", instanceStorage->transparency);
			}

		}
		else {

			if (instanceStorage->activeFloor == (instanceStorage->walls->location->vec.y / instanceStorage->floorDiferencial) && instanceStorage->activeFloor != 98) {
				instanceStorage->shader->setFloat("transparent", 1.0);
			}
			else if (instanceStorage->activeFloor == 90 || instanceStorage->activeFloor == 99) {
				instanceStorage->shader->setFloat("transparent", 0.8);
			}
			else {
				instanceStorage->shader->setFloat("transparent", instanceStorage->transparency);
			}

		}
	}
	else if (instanceStorage->Boidss != NULL) {
		if (instanceStorage->activeFloor == (instanceStorage->Boidss->location->vec.y / instanceStorage->floorDiferencial) && instanceStorage->activeFloor != 98) {
			instanceStorage->shader->setFloat("transparent", 1.0);
		}
		else if (instanceStorage->activeFloor == 90 || instanceStorage->activeFloor == 99) {
			instanceStorage->shader->setFloat("transparent", 1.0);
		}
		else {
			instanceStorage->shader->setFloat("transparent", instanceStorage->transparency);
		}
	}
	else if (instanceStorage->sky || instanceStorage->landscape){
		instanceStorage->shader->setFloat("transparent", 1.0);
	}

}