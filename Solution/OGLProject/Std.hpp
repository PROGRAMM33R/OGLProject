#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <iterator>
#include <cstdio>
#include <ctime>

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
#include <IL\il.h>
#include <SOIL.h>

#include <AntTweakBar.h>

#include "Config.hpp"
#include "Vertex.hpp"
#include "Texture.hpp"

#include "DrawTypeObj.hpp"

using namespace glm;
using namespace std;