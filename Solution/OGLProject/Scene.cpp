
#include "Std.hpp"
#include "Scene.hpp"

Scene::~Scene() {
	TwTerminate();
	glfwTerminate();
}

void Scene::error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

GLFWwindow *Scene::initScene(void) const {
	GLFWwindow *window = NULL;

	if (!glfwInit()){
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return window;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, cfg->OGL_MAJOR_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, cfg->OGL_MINOR_VERSION);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(this->cfg->WINDOW_WIDTH, this->cfg->WINDOW_HEIGHT, this->cfg->WINDOW_LABEL.c_str(), NULL, NULL);

	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not %d.%d compatible. Try another version.\n", cfg->OGL_MAJOR_VERSION, cfg->OGL_MINOR_VERSION);
		glfwSetErrorCallback(error_callback);
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
	glfwSetCursorPos(window, this->cfg->WINDOW_WIDTH / 2, this->cfg->WINDOW_HEIGHT / 2);
	glClearColor(0.15f, 0.15f, 0.15f, 0.0f);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	return window;
}