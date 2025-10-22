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

    double lastX = 540.0, lastY = 360.0; // centro inicial de la ventana
    bool firstMouse = true;
    float yaw = 0.0f;   // rotación horizontal (eje Y)
    float pitch = 0.0f; // rotación vertical (eje X)
    float zoom = 1.0f;  // escala con scroll

    bool curP = true, curG = true;

	std::vector<float> geometry
	{   //Vertices
		// x     y     z     w
		-0.5f, 0.5f, 0.0f, 1.0f, //vertice 1
		0.5f, 0.5f, 0.0f, 1.0f, //vertice 4
		-0.5f, -0.5f, 0.0f, 1.0f, //vertice 2
		0.5f, -0.5f, 0.0f, 1.0f, //vertice 3
		
		//Colores
		// R     G     B     A
		1.0f, 0.0f, 0.0f, 1.0f, //Color rojo
		0.0f, 1.0f, 0.0f, 1.0f, //Color verde
		0.0f, 0.0f, 1.0f, 1.0f //Color azul
	};

    std::vector<float> cube
    {
        //Cara frontal
        //Triangulo 1
        -0.5f,  0.5f,  0.5f, 1.0f,
        0.5f,  0.5f,  0.5f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f,
        //Triangulo 2
        0.5f,  0.5f,  0.5f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f,
        0.5f, -0.5f,  0.5f, 1.0f,

        //Cara trasera
        //Tri 1
        -0.5f,  0.5f, -0.5f, 1.0f,
        0.5f,  0.5f, -0.5f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f,
        //Tri 2
        0.5f,  0.5f, -0.5f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f,

        //Cara izquierda
        //Tri1
        -0.5f,  0.5f, -0.5f, 1.0f,
        -0.5f,  0.5f,  0.5f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f,
        //Tri2
        -0.5f,  0.5f,  0.5f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f,

        //Cara derecha
        //Tri1
        0.5f,  0.5f, -0.5f, 1.0f,
        0.5f,  0.5f,  0.5f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f,
        //Tri2
        0.5f,  0.5f,  0.5f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f,
        0.5f, -0.5f,  0.5f, 1.0f,

        //Cara superior
        //Tr1
        -0.5f,  0.5f, -0.5f, 1.0f,
        0.5f,  0.5f, -0.5f, 1.0f,
        -0.5f,  0.5f,  0.5f, 1.0f,
        //Tr2
        0.5f,  0.5f, -0.5f, 1.0f,
        -0.5f,  0.5f,  0.5f, 1.0f,
        0.5f,  0.5f,  0.5f, 1.0f,

        //Cara inferior
        //Tr1
        -0.5f, -0.5f, -0.5f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f,
        //Tr2
        0.5f, -0.5f, -0.5f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f,
        0.5f, -0.5f,  0.5f, 1.0f,

        //Colores
        1.0f, 0.0f, 0.0f, 1.0f, //rojo
        1.0f, 0.0f, 0.0f, 1.0f, //rojo
        1.0f, 0.0f, 0.0f, 1.0f, //rojo
        1.0f, 0.0f, 0.0f, 1.0f, //rojo
        1.0f, 0.0f, 0.0f, 1.0f, //rojo
        1.0f, 0.0f, 0.0f, 1.0f, //rojo
        0.0f, 1.0f, 0.0f, 1.0f, //verde
        0.0f, 1.0f, 0.0f, 1.0f, //verde
        0.0f, 1.0f, 0.0f, 1.0f, //verde
        0.0f, 1.0f, 0.0f, 1.0f, //verde
        0.0f, 1.0f, 0.0f, 1.0f, //verde
        0.0f, 1.0f, 0.0f, 1.0f, //verde
        0.0f, 0.0f, 1.0f, 1.0f, //azul
        0.0f, 0.0f, 1.0f, 1.0f, //azul
        0.0f, 0.0f, 1.0f, 1.0f, //azul
        0.0f, 0.0f, 1.0f, 1.0f, //azul
        0.0f, 0.0f, 1.0f, 1.0f, //azul
        0.0f, 0.0f, 1.0f, 1.0f, //azul
        1.0f, 1.0f, 0.0f, 1.0f, //amarillo
        1.0f, 1.0f, 0.0f, 1.0f, //amarillo
        1.0f, 1.0f, 0.0f, 1.0f, //amarillo
        1.0f, 1.0f, 0.0f, 1.0f, //amarillo
        1.0f, 1.0f, 0.0f, 1.0f, //amarillo
        1.0f, 1.0f, 0.0f, 1.0f, //amarillo
        1.0f, 0.5f, 0.0f, 1.0f, //naranja
        1.0f, 0.5f, 0.0f, 1.0f, //naranja
        1.0f, 0.5f, 0.0f, 1.0f, //naranja
        1.0f, 0.5f, 0.0f, 1.0f, //naranja
        1.0f, 0.5f, 0.0f, 1.0f, //naranja
        1.0f, 0.5f, 0.0f, 1.0f, //naranja
        1.0f, 1.0f, 1.0f, 1.0f, //blanco
        1.0f, 1.0f, 1.0f, 1.0f, //blanco
        1.0f, 1.0f, 1.0f, 1.0f, //blanco
        1.0f, 1.0f, 1.0f, 1.0f, //blanco
        1.0f, 1.0f, 1.0f, 1.0f, //blanco
        1.0f, 1.0f, 1.0f, 1.0f, //blanco
    };

	std::map<std::string, GLuint> ids;//izquierda llave y derecha valor

	glm::mat4 camera;
    glm::mat4 projection;
    glm::mat4 model;
	glm::vec3 eye{ 0.0f, 0.0f, 2.0f };
	glm::vec3 center{ 0.0f, 0.0f, 0.0f };

public:

	GLFWwindow* window; //Inicializa la ventana

	void setupGeometry();
	void setupProgram();

	void setupProgram2();
	void setupCube();

	void setup();
	void update();
	void draw();

	void keyCallback(int key, int scancode, int action, int mods);

    void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

    void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    void currentProgram();

    void currentGeometry();

    void cameraAndMove();
};