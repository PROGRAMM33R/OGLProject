
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

	Config		*cfg = argc == 2 ? cfg = new Config(argv[1]) : cfg = new Config("config.cfg");;
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

	Walls *walls = new Walls(map, cfg, controls);
	Flock *flock = new Flock(cfg, walls);
	Model *surface = new Model(cfg->OBJ_SURFACE, cfg);

	float lastTime = glfwGetTime(), currentTime = 0.0, fps = 0.0;
	int nbFrames = 0;

	InstanceStorage *ISSky = new InstanceStorage(shader, DRAW_TYPE_SKY, NULL, NULL);
	InstanceStorage *ISSurface = new InstanceStorage(shader, DRAW_TYPE_LANDSCAPE, NULL, NULL);
	ISSky->sky = true;
	ISSurface->landscape = true;

	Model *sky = new Model(cfg->OBJ_SKY, cfg);
	Model *landscape = new Model(cfg->OBJ_LANDSCAPE, cfg);

	Hud::init(cfg, &fps, &(controls->escapeDuration));

	do {

		shader->use();

		if (controls->updateViewPort)
		{
			glfwGetFramebufferSize(window, &controls->_vpSize[0], &controls->_vpSize[1]);
			glViewport(0, 0, controls->_vpSize[0], controls->_vpSize[1]);
			controls->updateViewPort = false;
		}

		currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) {
			fps = 1000.0 / (float)nbFrames;
			fps = (1 / fps) * 1000;
			nbFrames = 0;
			lastTime += 1.0;
		}

		glm::mat4 ModelMatrix = glm::mat4(2.0);
		shader->setMat4("Model", ModelMatrix);

		shader->setVec3("light.position", glm::vec3(0.0f, 100.0f, 150.0f));
		shader->setVec3("viewPos", controls->getCameraPosition());

		shader->setVec3("light.ambient", 1.0f, 1.0f, 1.0f);
		shader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
		shader->setVec3("light.specular", 0.8f, 0.8f, 0.8f);
		
		shader->setVec3("material.specular", 0.6f, 0.6f, 0.6f);
		shader->setFloat("material.shininess", 64.0f);

		// directional light
		/*shader->setVec3("dirLight.position", glm::vec3(14.0f, 10.0f, 6.0f));
		shader->setVec3("dirLight.ambient", 0.9f, 0.9f, 0.9f);
		shader->setVec3("dirLight.diffuse", 0.3f, 0.3f, 0.3f);
		shader->setVec3("dirLight.specular", 0.2f, 0.2f, 0.2f);*/

		controls->computeMatricesFromInputs( window );
		glm::mat4 MVP = controls->getMVP();

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ISSky->cameraX = controls->camera->getPosition_().x;
		ISSky->cameraY = controls->camera->getPosition_().y;
		ISSky->cameraZ = controls->camera->getPosition_().z;

		flock->flocking(shader);
		walls->drawWalls(shader);
		landscape->Draw(ISSurface);
		sky->Draw(ISSky);

		if (cfg->HUD_ENABLED == 1) Hud::draw();
		
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