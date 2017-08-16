#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/scene.h> // aiScene output data structure
#include <assimp/postprocess.h> // Post processing flags

using namespace glm;
using namespace std;

//float points[] = {
//	0.0f, 0.5f, 0.0f,
//	0.5f, -0.5f, 0.0f,
//	-0.5f, -0.5f, 0.0f
//};
//
//const char* vertex_shader =
//"#version 330\n"
//"layout(location=0) in vec3 vp;"
//"void main () {"
//"     gl_Position = vec4 (vp, 1.0);"
//"}";
//
//const char* fragment_shader =
//"#version 330\n"
//"out vec4 frag_colour;"
//"void main () {"
//"     frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
//"}";

int main(int argc, char **argv) {

	GLFWwindow* window;
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}
	glfwTerminate();

	Assimp::Importer importer;
	vec4 Position = glm::vec4(glm::vec3(0.0), 1.0);

	return 0;

}