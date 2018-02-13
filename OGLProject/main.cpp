
#include "Config.hpp"
#include "Scene.hpp"
#include "Shader.hpp"
#include "Controls.hpp"
#include "Model.hpp"
#include "Flock.hpp"
#include "Walls.hpp"
#include "Map.hpp"
#include "Hud.hpp"
#include "Std.hpp"

int main(int argc, char **argv) {

	Config		*cfg = new Config();
	Map         *map = new Map();
	GLFWwindow  *window = NULL;
	Scene       *scene = new Scene(cfg);
	Controls    *controls = new Controls(cfg);

	window = scene->initScene();
	if (window == NULL) {
		return -1;
	}

	Shader *shader = new Shader("VertexShader.shader", "FragmentShader.shader");
	GLuint MatrixID = glGetUniformLocation(shader->ID, "MVP");

	Walls *walls = new Walls(map, cfg);
	Flock *flock = new Flock(cfg, walls);
	Model *surface = new Model(cfg->OBJ_SURFACE, cfg);

	float lastTime = glfwGetTime(), currentTime = 0.0, fps = 0.0;
	int nbFrames = 0;

	Hud::init(cfg, &fps, &(controls->escapeDuration));

	do {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->use();

		currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) {
			fps = 1000.0 / (float)nbFrames;
			nbFrames = 0;
			lastTime += 1.0;
		}

		glm::mat4 ModelMatrix = glm::mat4(2.0);
		shader->setMat4("Model", ModelMatrix);

		shader->setVec3("light.position", glm::vec3(14.0f, 10.0f, 6.0f));
		shader->setVec3("viewPos", controls->getCameraPosition());

		shader->setVec3("light.ambient", 1.0f, 1.0f, 1.0f);
		shader->setVec3("light.diffuse", 0.0f, 0.0f, 0.0f);
		shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		
		shader->setVec3("material.specular", 0.0f, 0.0f, 0.0f);
		shader->setFloat("material.shininess", 64.0f);

		// directional light
		/*shader->setVec3("dirLight.position", glm::vec3(14.0f, 10.0f, 6.0f));
		shader->setVec3("dirLight.ambient", 0.9f, 0.9f, 0.9f);
		shader->setVec3("dirLight.diffuse", 0.3f, 0.3f, 0.3f);
		shader->setVec3("dirLight.specular", 0.2f, 0.2f, 0.2f);*/

		controls->computeMatricesFromInputs( window );
		glm::mat4 MVP = controls->getMVP();

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		walls->drawWalls(shader);
		flock->flocking(shader);

		surface->Draw(shader, DRAW_TYPE_SURFACE);

		Hud::draw();

		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	delete cfg;
	delete map;
	delete scene;
	delete shader;
	delete controls;
	delete flock;
	delete walls;

	return 0;

}