#version 460 core //Versi�n 4.60 de OpenGL

in vec4 vertexColor; //Llega de vertexshader
out vec4 outColor; //A la salida del Fragment Shader da un color
uniform float time;

void main()
{
	//outColor = vec4(1.0f, 0.0f, 0.0f, 1.0f); //RGBA, saldr� color rojo
	outColor = vertexColor; //Recibe el color por el vertexColor del vertexshader y se pone en outColor
}

//En todas las ejecuciones del fragmentshader
//uniform tendr�n el mismo valor
//in y out cambian los valores