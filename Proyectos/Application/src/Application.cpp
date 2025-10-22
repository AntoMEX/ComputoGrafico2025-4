#include "Application.h"
#include "ShaderFuncs.h"
#include <iostream>

//Triangulo
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
//Cubo
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
//Programa con movimiento en x
void Application::setupProgram()
{
	std::string vertexShader = leerArchivo("Shaders/VertexShader.glsl");
	std::string fragmentShader = leerArchivo("Shaders/FragmentShader.glsl"); //Lee el archivo y lo guarda en texto

	ids["Programa"] = InitializeProgram(vertexShader, fragmentShader); //Guardar en el mapa el id del mapa

	ids["Time"] = glGetUniformLocation(ids["Programa"], "time");

	ids["DirX"] = glGetUniformLocation(ids["Programa"], "dirX");
}
//Programa con movimiento de cámara y mouse
void Application::setupProgram2()
{
	std::string vertexShader = leerArchivo("Shaders/VertexCamera.glsl");
	std::string fragmentShader = leerArchivo("Shaders/FragmentCamera.glsl"); //Lee el archivo y lo guarda en texto

	ids["Programa2"] = InitializeProgram(vertexShader, fragmentShader); //Guardar en el mapa el id del mapa

	ids["Time2"] = glGetUniformLocation(ids["Programa2"], "time");

	ids["Camera"] = glGetUniformLocation(ids["Programa2"], "camera");
	ids["Projection"] = glGetUniformLocation(ids["Programa2"], "projection");
	ids["Model"] = glGetUniformLocation(ids["Programa2"], "model");
}
//Inputs
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

	if (key == GLFW_KEY_1 && action == GLFW_PRESS) 
	{
		curP = true;
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) 
	{
		curP = false;
	}
	if (key == GLFW_KEY_T && action == GLFW_PRESS)
	{
		curG = true;
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		curG = false;
	}
}
//Cursor
void Application::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse) 
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = ypos - lastY;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.3f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset; //mover mouse en X rotar en Y
	pitch += yoffset; //mover mouse en Y rotar en X
}
//Scroll
void Application::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	zoom += (float)yoffset * 0.1f; //cada paso de scroll cambia la escala
	if (zoom < 0.1f) zoom = 0.1f;
	if (zoom > 3.0f) zoom = 3.0f;
}

//Programa actual
void Application::currentProgram()
{
	if (curP == true)
	{
		glUseProgram(ids["Programa"]);
	}
	if (curP == false)
	{
		glUseProgram(ids["Programa2"]);
	}
}
//Geometria actual
void Application::currentGeometry()
{
	if (curG == true)
	{
		glBindVertexArray(ids["Triangle"]);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	if (curG == false)
	{
		glBindVertexArray(ids["Cube"]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}
//Datos extra para movimiento y cámara
void Application::cameraAndMove()
{
	glUniform1f(ids["Time"], time);
	glUniform1f(ids["Time2"], time);

	glUniformMatrix4fv(ids["Model"], 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(ids["Camera"], 1, GL_FALSE, &camera[0][0]);
	glUniformMatrix4fv(ids["Projection"], 1, GL_FALSE, &projection[0][0]);

	glUniform1f(ids["DirX"], dirX);
}
//Setup de todo
void Application::setup()
{
	setupGeometry();
	setupCube();
	setupProgram();
	setupProgram2();
	projection = glm::perspective(45.0f, 1080.0f / 720.0f, 0.1f, 100.0f);
	glEnable(GL_DEPTH_TEST);
}
//Actualización
void Application::update() 
{
	time += 0.01f;
	//Camara
	eye = glm::vec3(0.0f, 0.0f, 3.0f /* + cos(time)*/);
	camera = glm::lookAt(eye, center, glm::vec3(0.0f, 1.0f, 0.0f));
	//Escala con scroll
	//glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f,1.5f,1.0f));
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(zoom));
	//glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//Rotaciones con mouse
	glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
	//glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = rotY * rotX * scale;
	//model = rotateX * translate * scale;
}
//Dibujado de todo
void Application::draw() 
{
	currentProgram();
	cameraAndMove();
	currentGeometry();
}