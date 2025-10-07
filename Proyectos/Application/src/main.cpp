#include "glad.h"
#include <GLFW/glfw3.h>
#include "Application.h"


int main(void)
{
    //Etapa de setup
    GLFWwindow* window; //Inicializa la ventana
    Application app;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1080, 720, "Hello Application", NULL, NULL);
    if (!window) //Si falla
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window); //Ligar Windows con openGL

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        //Manejar error
        //glfwGetProcAddress es la funcion que GLFW proporciona para obtener las direcciones
        //de las funciones de OpenGL, que es lo que GLAD necesita para cargar
        return -1;
    }

    app.setup();

    //Termina la etapa de setup

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        app.update();

        app.draw();
    }

    glfwTerminate();
    return 0;
}