#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

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
	static float			SPEED = 1500.0f;
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

	static void init() {

		vector<string> *keys = new vector<string>();
		vector<string> *values = new vector<string>();

		std::ifstream in("Config.cfg");
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
					cout << "key: " << key;
					cout << ", value: " << value << endl;
				}
			}
		}

		for (register unsigned int i = 0; i < keys->size(); i++) {

			if (keys->at(i).find("WINDOW_LABEL") != std::string::npos) {
				Config::WINDOW_LABEL = values->at(i);
			}

		}

	}

};