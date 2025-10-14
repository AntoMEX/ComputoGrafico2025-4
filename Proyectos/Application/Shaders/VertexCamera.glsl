#version 460 core  //Versión 4.60 de OpenGL

layout (location = 0) in vec4 vPosition; //Abre canal de comunicación con el exterior, primer canal es el 0, resive un vector de 4 dimensiones
//vPosition de vertices

layout (location = 1) in vec4 vColor; //Abre canal de comunicación con el exterior, segundo canal es el 1, resive un vector de 4 dimensiones
//vColor de color
out vec4 vertexColor; //Sale de vertexshader
uniform float time; //Sirven para comunicar con C++

uniform float dirX;

void main()
{
	vertexColor = vColor; //El vertexColor es los colores del vColor
	vec4 newPos = vPosition;

	newPos.x += dirX + cos(time);

	gl_Position = newPos; //Posicion del vertice
}

//En todas las ejecuciones del fragmentshader
//uniform tendrán el mismo valor
//in y out cambian los valores