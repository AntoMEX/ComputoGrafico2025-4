#pragma once
#include <vector>
#include <map>
#include <iostream>
#include "glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Application 
{
private:
	float time = { 0.0f };

	float dirX = 0.0f;

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

	glm::mat4 camera;
	glm::vec3 eye{ 0.0f, 0.0f, 2.0f };
	glm::vec3 center{ 0.0f, 0.0f, 0.0f };

public:

	GLFWwindow* window; //Inicializa la ventana

	void setupGeometry();
	void setupProgram();

	/*void setupProgram1();
	void setupProgram2();*/

	void setup();
	void update();
	void draw();

	void keyCallback(int key, int scancode, int action, int mods);

};