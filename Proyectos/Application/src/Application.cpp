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
		sizeof(GLfloat) * geometry.size(), //Calculo de tamaño en bytes de todo el arreglo
		&geometry[0], GL_STATIC_DRAW); //Mandamos la geometria al buffer

	//Vertices
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0); //primer indice, tamaño (vertices de 4 valores), 
	glEnableVertexAttribArray(0);                     //cada uno flotante, datos no normales son vertices, cuantos bytes deben pasar 
	                                                  //para encontrar el siguiente vertice y desde el 0 va el primer valor
	//Colores
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const void*)(16*sizeof(float))); //segundo indice, tamaño (vertices de 4 valores), cada uno flotante, 
	glEnableVertexAttribArray(1);                          //datos no normales porque son vertices, cuantos bytes deben pasar 
														   //para encontrar el siguiente vertice y desde el 0 va el primer valor
}

void Application::setupProgram()
{
	std::string vertexShader = leerArchivo("Shaders/VertexShader.glsl");
	std::string fragmentShader = leerArchivo("Shaders/FragmentShader.glsl"); //Lee el archivo y lo guarda en texto

	ids["Programa"] = InitializeProgram(vertexShader, fragmentShader); //Guardar en el mapa el id del mapa

	ids["Time"] = glGetUniformLocation(ids["Programa"], "time");

	ids["DirX"] = glGetUniformLocation(ids["Programa"], "dirX");
}

//void Application::setupProgram1()
//{
//	std::string vertexShader = leerArchivo("Shaders/VertexShader.glsl");
//	std::string fragmentShader = leerArchivo("Shaders/FragmentShader.glsl"); //Lee el archivo y lo guarda en texto
//
//	ids["Programa1"] = InitializeProgram(vertexShader, fragmentShader); //Guardar en el mapa el id del mapa
//
//	ids["Time"] = glGetUniformLocation(ids["Programa"], "time");
//
//	ids["DirX"] = glGetUniformLocation(ids["Programa"], "dirX");
//}
//
//void Application::setupProgram2()
//{
//	std::string vertexShader = leerArchivo("Shaders/VertexShader.glsl");
//	std::string fragmentShader = leerArchivo("Shaders/FragmentShader.glsl"); //Lee el archivo y lo guarda en texto
//
//	ids["Programa2"] = InitializeProgram(vertexShader, fragmentShader); //Guardar en el mapa el id del mapa
//
//	ids["Time"] = glGetUniformLocation(ids["Programa"], "time");
//
//	ids["DirX"] = glGetUniformLocation(ids["Programa"], "dirX");
//}

void Application::keyCallback(int key, int scancode, int action, int mods) 
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS) 
	{
		dirX -= 0.05f; 
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		dirX += 0.05f; 
	}
}

void Application::setup()
{
	setupGeometry();
	setupProgram();
	/*setupProgram1();
	setupProgram2();*/
}

void Application::update() 
{
	time += 0.001f;
	camera = glm::lookAt(eye, center, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Application::draw() 
{
	glUseProgram(ids["Programa"]);

	//glUseProgram(ids["Programa1"]);

	glUniform1f(ids["Time"], time);

	glUniform1f(ids["DirX"], dirX);

	glBindVertexArray(ids["Triangle"]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}