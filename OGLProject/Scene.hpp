#pragma once

#include "Std.hpp"
#include "Config.hpp"

class Scene {

private:
public:
	Scene() {}
	~Scene();
	GLFWwindow *initScene(void) const;
	void deleteBuffers(
		GLuint *VertexArrayID, 
		GLuint *vertexbuffer, 
		GLuint *uvbuffer,
		GLuint *normalbuffer,
		GLuint *indexbuffer,
		GLuint programID) const;

};