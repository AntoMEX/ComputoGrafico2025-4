#version 460 core //Versi�n 4.60 de OpenGL

out vec4 outColor; //A la salida del Fragment Shader da un color

void main()
{
	outColor = vec4(1.0f, 0.0f, 0.0f, 1.0f); //RGBA, saldr� color rojo
}