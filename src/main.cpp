#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "logger.cpp"

int main()
{
    Logger logger;

    logger.log(INFO, "Hello from Shadematica!");

    if (!glfwInit()) {
        logger.log(ERROR, "glfw could not initialize");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    logger.log(INFO, "creating window..");
    GLFWwindow* window = glfwCreateWindow(800, 600, "Shadematica", NULL, NULL);
    if (window == NULL)
    {
        logger.log(ERROR, "glfw could not initialize window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        logger.log(ERROR, "glad could not initialize");
        return -1;
    }

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // render
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}