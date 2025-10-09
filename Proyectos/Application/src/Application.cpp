#include "Application.h"
#include "ShaderFuncs.h"
#include <iostream>

void Application::setupGeometry()
{
	//Crear VAO
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	ids["Triangle"] = VAO;

	glBindVertexArray(VAO);

	//Crear VBO vertices
	glGenBuffers(1, &VBO); //Crea buffer

	glBindBuffer(GL_ARRAY_BUFFER, VBO); //Todavia no reserva memoria

	//Pasar arreglo de vertices
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(GLfloat) * geometry.size(), //Calculo de tamaño en bytes
		&geometry[0], GL_STATIC_DRAW); //Mandamos la geometria al buffer

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glDisableVertexAttribArray(0);

	//d::cout << "setup()" << std::endl;
}

void Application::setupProgram()
{
	std::string vertexShader = leerArchivo("Shaders/VertexShader.glsl");
	std::string fragmentShader = leerArchivo("Shaders/FragmentShader.glsl"); //Lee el archivo y lo guarda en texto

	ids["Programa"] = InitializeProgram(vertexShader, fragmentShader); //Guardar en el mapa el id del mapa
}

void Application::setup()
{
	setupGeometry();
	setupProgram();
}

void Application::update() 
{

}

void Application::draw() 
{
	glUseProgram(ids["Programa"]);

	glBindVertexArray(ids["Triangle"]);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}