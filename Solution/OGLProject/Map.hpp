#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

class Map {

public:
	vector<vector<char>*> *map;

	Map() {

		std::ifstream in("map.txt");
		std::string contents((std::istreambuf_iterator<char>(in)),
			std::istreambuf_iterator<char>());

		const char *_map = contents.c_str();

		std::istringstream is_file(_map);

		std::string line;

		int index = 0;
		map = new vector<vector<char>*>();

		while (std::getline(is_file, line))
		{
			
			map->push_back(new vector<char>());

			for (char& c : line) {
				map->at(index)->push_back(c);
			}

			index++;

		}

	}

};