
#include "Std.hpp"
#include "Scene.hpp"

Scene::~Scene() {
	glfwTerminate();
}

GLFWwindow *Scene::initScene(void) const {
	GLFWwindow *window = NULL;

	if (!glfwInit()){
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return window;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(config::WINDOW_WIDTH, config::WINDOW_HEIGHT, config::WINDOW_LABEL.c_str(), NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return window;
	}
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return window;
	}
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwPollEvents();
	glfwSetCursorPos(window, config::WINDOW_WIDTH / 2, config::WINDOW_HEIGHT / 2);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	return window;
}

void Scene::deleteBuffers(GLuint *VertexArrayID, GLuint *vertexbuffer, GLuint *uvbuffer, GLuint programID) const {
	glDeleteVertexArrays(1, VertexArrayID);
	glDeleteBuffers(1, vertexbuffer);
	glDeleteBuffers(1, uvbuffer);
	glDeleteProgram(programID);
}