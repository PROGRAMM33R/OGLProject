
#include "Std.hpp"
#include "Scene.hpp"
#include "Shader.hpp"
#include "Controls.hpp"
#include "Model.hpp"

int main(int argc, char **argv) {

	GLFWwindow      *window = NULL;
	Scene           *scene = new Scene();
	Controls        *controls = new Controls();

	window = scene->initScene();
	if (window == NULL) {
		return -1;
	}

	Shader *shader = new Shader("VertexShader.shader", "FragmentShader.shader");
	GLuint MatrixID = glGetUniformLocation(shader->ID, "MVP");

	Model *model = new Model("Models/cottage/test.obj");
	Model *surface = new Model("Models/surface/surface.obj");

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	do {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->use();

		glm::mat4 ModelMatrix = glm::mat4(1.0);
		/*shader->setMat4("Model", ModelMatrix);
		shader->setVec3("light.position", glm::vec3(14.0f, 10.0f, 6.0f));
		shader->setVec3("viewPos", controls->getCameraPosition());

		shader->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
		shader->setVec3("light.diffuse", 0.9f, 0.9f, 0.9f);
		shader->setVec3("light.specular", 0.2f, 0.2f, 0.2f);
		
		shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		shader->setFloat("material.shininess", 64.0f);*/

		// directional light
		shader->setMat4("Model", ModelMatrix);
		shader->setVec3("viewPos", controls->getCameraPosition());
		shader->setVec3("dirLight.position", glm::vec3(14.0f, 10.0f, 6.0f));
		shader->setVec3("dirLight.ambient", 0.2f, 0.2f, 0.2f);
		shader->setVec3("dirLight.diffuse", 0.9f, 0.9f, 0.9f);
		shader->setVec3("dirLight.specular", 0.2f, 0.2f, 0.2f);

		controls->computeMatricesFromInputs( window );
		glm::mat4 MVP = controls->getMVP();

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		model->Draw(shader->ID);
		surface->Draw(shader->ID);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	delete scene;
	delete shader;
	delete controls;

	return 0;

}