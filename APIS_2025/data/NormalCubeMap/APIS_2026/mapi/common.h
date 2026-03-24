#pragma once
#include <iostream>
#pragma once
#define _USE_MATH_DEFINES
#ifdef GLAD_BIN
#define GLAD_GL_IMPLEMENTATION
#endif
#include <glad/gl.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>

#include <iostream>
#include <vector>
#include <list>

#include <map>
#include <fstream>
#include <string>
#include <math.h>

#include <iostream>
#include <fstream>
#include <sstream>
using namespace glm;
using namespace std;

template <typename T>
std::vector<T> splitString(const std::string& str, char delim) {
	std::vector<T> elems;
	std::stringstream sstream(str);
	std::string item;
	T tipoDato;
	if (str != "") {
		while (std::getline(sstream, item, delim))
		{
			std::istringstream str(item);
			str >> tipoDato;
			elems.push_back(tipoDato);
		}
	}
	return elems;
}
