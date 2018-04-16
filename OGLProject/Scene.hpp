#pragma once

#include "Std.hpp"

class Scene {

private:
	Config *cfg;

public:
	Scene(Config *cfg)
	:
		cfg(cfg) {}
	~Scene();
	GLFWwindow *initScene(void) const;
	static void error_callback(int error, const char* description);

};