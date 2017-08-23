
#include "Std.hpp"
#include "Scene.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Controls.hpp"
#include "Loader.hpp"

int main(int argc, char **argv) {

	GLFWwindow   *window = NULL;
	Scene        *scene = new Scene();
	Shader       *shader = new Shader();
	Texture      *texture = new Texture();
	Controls     *controls = new Controls();
	Loader       *loader = new Loader();

	window = scene->initScene();
	if (window == NULL) {
		return -1;
	}

	GLuint VertexArrayID, vertexbuffer, uvbuffer, indexbuffer;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint programID = shader->LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	GLuint Texture = texture->load("Models/cube/test.png");
	GLuint TextureID = glGetUniformLocation(programID, "OGLProject");

	std::vector<unsigned short> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	bool res = loader->loadAssImp("Models/cube/test.obj", indices, vertices, uvs, normals);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	do {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);
		controls->computeMatricesFromInputs( window );
		glm::mat4 MVP = controls->getMVP();

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		glDrawArrays(GL_TRIANGLES, 0, vertices.size());

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	scene->deleteBuffers(&VertexArrayID, &vertexbuffer, &uvbuffer, programID);
	glDeleteTextures(1, &Texture); // TODO

	delete scene;
	delete shader;
	delete texture;
	delete controls;
	delete loader;

	return 0;

}