#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <glm/vec3.hpp> // glm::vec3
#include <iostream>

using namespace glm;
using namespace std;

class Config {

public:
		std::string     WINDOW_LABEL = "Bachelor";
		int				WINDOW_WIDTH;
		int				WINDOW_HEIGHT;
		glm::vec3		INIT_CAMERA_POSITION;
		float			FOV;
		float			PLAYER_SPEED;
		float			MOUSE_SPEED;

		int				BOID_CUBE_SIZE;
		int				BOID_OBJ_SIZE;
		int				BOID_NUMBER_OF_BOIDS;
		int				BOID_NUMBER_OF_PREDATORS;
		int				BOID_GENERATE_SPACE;
		int				BOID_DESIRED_SEPARATION;
		int				BOID_NEIGHTBORDIST;
		float			BOID_MAX_SPEED;
		float			BOID_MAX_FORCE;
		float			BOID_MAX_SPEED_PREDATOR;
		float			BOID_MAX_FORCE_PREDATOR;

		std::string		OBJ_SURFACE;
		std::string		OBJ_BOID;
		std::string		OBJ_PREDATOR;

		Config() {

			vector<string> *keys = new vector<string>();
			vector<string> *values = new vector<string>();

			int cameraX = 0, cameraY = 0, cameraZ = 0;
			int cubeSize = 0;
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
					WINDOW_LABEL = values->at(i);
				}
				if (keys->at(i).find("WINDOW_WIDTH") != std::string::npos) {
					WINDOW_WIDTH = std::stoi(values->at(i));
				}
				if (keys->at(i).find("WINDOW_HEIGHT") != std::string::npos) {
					WINDOW_HEIGHT = std::stoi(values->at(i));
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
					FOV = std::stof(values->at(i));
				}
				if (keys->at(i).find("PLAYER_SPEED") != std::string::npos) {
					PLAYER_SPEED = std::stof(values->at(i));
				}
				if (keys->at(i).find("MOUSE_SPEED") != std::string::npos) {
					MOUSE_SPEED = std::stof(values->at(i));
				}
				if (keys->at(i).find("BOID_CUBE_SIZE") != std::string::npos) {
					int cubeSize = std::stoi(values->at(i));
				}
				if (keys->at(i).find("BOID_OBJ_SIZE") != std::string::npos) {
					BOID_OBJ_SIZE = std::stoi(values->at(i));
				}
				if (keys->at(i).find("BOID_NUMBER_OF_BOIDS") != std::string::npos) {
					BOID_NUMBER_OF_BOIDS = std::stoi(values->at(i));
				}
				if (keys->at(i).find("BOID_NUMBER_OF_PREDATORS") != std::string::npos) {
					BOID_NUMBER_OF_PREDATORS = std::stoi(values->at(i));
				}
				if (keys->at(i).find("BOID_GENERATE_SPACE") != std::string::npos) {
					BOID_GENERATE_SPACE = std::stoi(values->at(i));
				}
				if (keys->at(i).find("BOID_DESIRED_SEPARATION") != std::string::npos) {
					BOID_DESIRED_SEPARATION = std::stoi(values->at(i));
				}
				if (keys->at(i).find("BOID_NEIGHTBORDIST") != std::string::npos) {
					BOID_NEIGHTBORDIST = std::stoi(values->at(i));
				}
				if (keys->at(i).find("BOID_SPEED") != std::string::npos) {
					BOID_MAX_SPEED = std::stof(values->at(i));
				}
				if (keys->at(i).find("BOID_FORCE") != std::string::npos) {
					BOID_MAX_FORCE = std::stof(values->at(i));
				}
				if (keys->at(i).find("BOID_MAX_SPEED_PREDATOR") != std::string::npos) {
					BOID_MAX_SPEED_PREDATOR = std::stof(values->at(i));
				}
				if (keys->at(i).find("BOID_MAX_FORCE_PREDATOR") != std::string::npos) {
					BOID_MAX_FORCE_PREDATOR = std::stof(values->at(i));
				}
				if (keys->at(i).find("OBJ_SURFACE") != std::string::npos) {
					OBJ_SURFACE = values->at(i);
				}
				if (keys->at(i).find("OBJ_BOID") != std::string::npos) {
					OBJ_BOID = values->at(i);
				}
				if (keys->at(i).find("OBJ_PREDATOR") != std::string::npos) {
					OBJ_PREDATOR = values->at(i);
				}
				INIT_CAMERA_POSITION = glm::vec3(cameraX, cameraY, cameraZ);
				if (BOID_GENERATE_SPACE >= BOID_CUBE_SIZE) {
					BOID_CUBE_SIZE = BOID_CUBE_SIZE + (BOID_GENERATE_SPACE - BOID_CUBE_SIZE);
				}
				if ((BOID_NUMBER_OF_BOIDS * 80) > cubeSize) {
					BOID_CUBE_SIZE = BOID_NUMBER_OF_BOIDS * 80;
				}
			}
			keys->clear();
			values->clear();
			delete keys;
			delete values;
		}

};
