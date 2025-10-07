#pragma once
#include <vector>
#include <map>
#include "glad.h"

class Application 
{
private:
	std::vector<float> geometry
	{  // x     y     z     w
		-1.0f, 1.0f, 0.0f, 1.0f, //vertice 1
		-1.0f, -1.0f, 0.0f, 1.0f, //vertice 2
		1.0f, -1.0f, 0.0f, 1.0f, //vertice 3
	};

	std::map<std::string, GLuint> ids;//izquierda llave y derecha valor

public:

	void setup();
	void update();
	void draw();
};