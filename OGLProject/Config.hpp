#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <glm/vec3.hpp> // glm::vec3
#include <iostream>

using namespace glm;
using namespace std;

namespace Config {

	static std::string      WINDOW_LABEL = "Bachelor";
	static int				WINDOW_WIDTH = 1024;
	static int				WINDOW_HEIGHT = 568;
	static glm::vec3		INIT_CAMERA_POSITION = glm::vec3(0, 1000, 2000);
	static float			FOV = 45.0f;
	static float			PLAYER_SPEED = 1500.0f;
	static float			MOUSE_SPEED = 0.005f;

	static int				BOID_CUBE_SIZE = 4100;
	static int				BOID_OBJ_SIZE = 7;
	static int				BOID_NUMBER_OF_BOIDS = 50;
	static int				BOID_NUMBER_OF_PREDATORS = 2;
	static int				BOID_GENERATE_SPACE = 800;
	static int				BOID_DESIRED_SEPARATION = 80;
	static int				BOID_NEIGHTBORDIST = 200;
	static float			BOID_MAX_SPEED = 25.5;
	static float			BOID_MAX_FORCE = 10.5;
	static float			BOID_MAX_SPEED_PREDATOR = 15.5;
	static float			BOID_MAX_FORCE_PREDATOR = 0.5;

	static std::string		OBJ_SURFACE = "Models/surface/surface.obj";
	static std::string		OBJ_BOID = "Models/cube/cube.obj";
	static std::string		OBJ_PREDATOR = "Models/cube_predator/cube.obj";

};

static void initConfig() {

	vector<string> *keys = new vector<string>();
	vector<string> *values = new vector<string>();

	int cameraX = 0, cameraY = 0, cameraZ = 0;
	std::ifstream in("config.cfg");
	std::string contents((std::istreambuf_iterator<char>(in)),
		std::istreambuf_iterator<char>());

	const char *config = contents.c_str();

	std::istringstream is_file(config);

	std::string line;

	while (std::getline(is_file, line))
	{
		std::istringstream is_line(line);
		std::string key;
		if (std::getline(is_line, key, '='))
		{
			std::string value;
			if (std::getline(is_line, value)) {
				keys->push_back(key);
				values->push_back(value);
			}
		}
	}

	for (register unsigned int i = 0; i < keys->size(); i++) {

		if (keys->at(i).find("WINDOW_LABEL") != std::string::npos) {
			Config::WINDOW_LABEL = values->at(i);
		}
		if (keys->at(i).find("WINDOW_WIDTH") != std::string::npos) {
			Config::WINDOW_WIDTH = std::stoi(values->at(i));
		}
		if (keys->at(i).find("WINDOW_HEIGHT") != std::string::npos) {
			Config::WINDOW_HEIGHT = std::stoi(values->at(i));
		}
		if (keys->at(i).find("INIT_CAMERA_POSITION_X") != std::string::npos) {
			cameraX = std::stoi(values->at(i));
		}
		if (keys->at(i).find("INIT_CAMERA_POSITION_Y") != std::string::npos) {
			cameraY = std::stoi(values->at(i));
		}
		if (keys->at(i).find("INIT_CAMERA_POSITION_Z") != std::string::npos) {
			cameraZ = std::stoi(values->at(i));
		}
		if (keys->at(i).find("FOV") != std::string::npos) {
			Config::FOV = std::stof(values->at(i));
		}
		if (keys->at(i).find("PLAYER_SPEED") != std::string::npos) {
			Config::PLAYER_SPEED = std::stof(values->at(i));
		}
		if (keys->at(i).find("MOUSE_SPEED") != std::string::npos) {
			Config::MOUSE_SPEED = std::stof(values->at(i));
		}
		if (keys->at(i).find("BOID_CUBE_SIZE") != std::string::npos) {
			Config::BOID_CUBE_SIZE = std::stoi(values->at(i));
		}
		if (keys->at(i).find("BOID_OBJ_SIZE") != std::string::npos) {
			Config::BOID_OBJ_SIZE = std::stoi(values->at(i));
		}
		if (keys->at(i).find("BOID_NUMBER_OF_BOIDS") != std::string::npos) {
			Config::BOID_NUMBER_OF_BOIDS = std::stoi(values->at(i));
		}
		if (keys->at(i).find("BOID_NUMBER_OF_PREDATORS") != std::string::npos) {
			Config::BOID_NUMBER_OF_PREDATORS = std::stoi(values->at(i));
		}
		if (keys->at(i).find("BOID_GENERATE_SPACE") != std::string::npos) {
			Config::BOID_GENERATE_SPACE = std::stoi(values->at(i));
		}
		if (keys->at(i).find("BOID_DESIRED_SEPARATION") != std::string::npos) {
			Config::BOID_DESIRED_SEPARATION = std::stoi(values->at(i));
		}
		if (keys->at(i).find("BOID_NEIGHTBORDIST") != std::string::npos) {
			Config::BOID_NEIGHTBORDIST = std::stoi(values->at(i));
		}
		if (keys->at(i).find("BOID_MAX_SPEED") != std::string::npos) {
			Config::BOID_MAX_SPEED = std::stof(values->at(i));
		}
		if (keys->at(i).find("BOID_MAX_FORCE") != std::string::npos) {
			Config::BOID_MAX_FORCE = std::stof(values->at(i));
		}
		if (keys->at(i).find("BOID_MAX_SPEED_PREDATOR") != std::string::npos) {
			Config::BOID_MAX_SPEED_PREDATOR = std::stof(values->at(i));
		}
		if (keys->at(i).find("BOID_MAX_FORCE_PREDATOR") != std::string::npos) {
			Config::BOID_MAX_FORCE_PREDATOR = std::stof(values->at(i));
		}
		if (keys->at(i).find("OBJ_SURFACE") != std::string::npos) {
			Config::OBJ_SURFACE = values->at(i);
		}
		if (keys->at(i).find("OBJ_BOID") != std::string::npos) {
			Config::OBJ_BOID = values->at(i);
		}
		if (keys->at(i).find("OBJ_PREDATOR") != std::string::npos) {
			Config::OBJ_PREDATOR = values->at(i);
		}
		Config::INIT_CAMERA_POSITION = glm::vec3(cameraX, cameraY, cameraZ);
		if (Config::BOID_GENERATE_SPACE >= Config::BOID_CUBE_SIZE) {
			Config::BOID_CUBE_SIZE = Config::BOID_GENERATE_SPACE - Config::BOID_CUBE_SIZE;
		}
	}

}