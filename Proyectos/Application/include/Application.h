#pragma once
#include <vector>
#include <map>
#include <iostream>
#include "glad.h"

class Application 
{
private:
	float time = { 0.0f };
	std::vector<float> geometry
	{   //Vertices
		// x     y     z     w
		-1.0f, 1.0f, 0.0f, 1.0f, //vertice 1
		1.0f, 1.0f, 0.0f, 1.0f, //vertice 4
		-1.0f, -1.0f, 0.0f, 1.0f, //vertice 2
		1.0f, -1.0f, 0.0f, 1.0f, //vertice 3
		
		//Colores
		// R     G     B     A
		1.0f, 0.0f, 0.0f, 1.0f, //Color rojo
		0.0f, 1.0f, 0.0f, 1.0f, //Color verde
		0.0f, 0.0f, 1.0f, 1.0f //Color azul
	};

	std::map<std::string, GLuint> ids;//izquierda llave y derecha valor

public:

	void setupGeometry();
	void setupProgram();

	void setup();
	void update();
	void draw();
};