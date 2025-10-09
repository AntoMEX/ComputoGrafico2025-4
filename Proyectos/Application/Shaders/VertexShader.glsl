#version 460 core  //Versión 4.60 de OpenGL

layout (location = 0) in vec4 vPosition; //Abre canal de comunicación con el exterior, primer canal es el 0, resive un vector de 4 dimensiones
//vPosition es el vertice

void main()
{
	gl_Position = vPosition; //Posicion del vertice
}