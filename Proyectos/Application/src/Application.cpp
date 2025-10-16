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

void Application::setupCube()
{
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	ids["Cube"] = VAO;

	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER,
		sizeof(GLfloat) * cube.size(),
		&cube[0], GL_STATIC_DRAW);

	//Vértices
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	//Colores
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const void*)(144 * sizeof(float)));
	glEnableVertexAttribArray(1);

}

void Application::setupProgram()
{
	std::string vertexShader = leerArchivo("Shaders/VertexShader.glsl");
	std::string fragmentShader = leerArchivo("Shaders/FragmentShader.glsl"); //Lee el archivo y lo guarda en texto

	ids["Programa"] = InitializeProgram(vertexShader, fragmentShader); //Guardar en el mapa el id del mapa

	ids["Time"] = glGetUniformLocation(ids["Programa"], "time");

	ids["DirX"] = glGetUniformLocation(ids["Programa"], "dirX");
}

void Application::setupProgram2()
{
	std::string vertexShader = leerArchivo("Shaders/VertexCamera.glsl");
	std::string fragmentShader = leerArchivo("Shaders/FragmentCamera.glsl"); //Lee el archivo y lo guarda en texto

	ids["Programa2"] = InitializeProgram(vertexShader, fragmentShader); //Guardar en el mapa el id del mapa

	ids["Time"] = glGetUniformLocation(ids["Programa2"], "time");

	ids["Camera"] = glGetUniformLocation(ids["Programa2"], "camera");
	ids["Projection"] = glGetUniformLocation(ids["Programa2"], "projection");
	ids["Model"] = glGetUniformLocation(ids["Programa2"], "model");
}

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
	//setupGeometry();
	setupCube();
	//setupProgram();
	setupProgram2();
	projection = glm::perspective(45.0f, 1080.0f / 720.0f, 0.1f, 100.0f);
	glEnable(GL_DEPTH_TEST);
}

void Application::update() 
{
	time += 0.01f;
	eye = glm::vec3(0.0f, 0.0f, 2.0f + cos(time));
	camera = glm::lookAt(eye, center, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f,1.5f,1.0f));
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	model = rotateX * translate * scale;
}

void Application::draw() 
{
	//glUseProgram(ids["Programa"]);

	glUseProgram(ids["Programa2"]);

	glUniform1f(ids["Time"], time);

	glUniformMatrix4fv(ids["Model"], 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(ids["Camera"], 1, GL_FALSE, &camera[0][0]);
	glUniformMatrix4fv(ids["Projection"], 1, GL_FALSE, &projection[0][0]);

	glUniform1f(ids["DirX"], dirX);

	/*glBindVertexArray(ids["Triangle"]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);*/

	glBindVertexArray(ids["Cube"]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}