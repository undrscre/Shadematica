#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "logger.h"
#include "graphics/renderer.h"

int main()
{
    log(INFO, MAIN, "Hello from Shadematica!");

    if (!glfwInit()) {
        log(ERROR, MAIN, "glfw could not initialize");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    log(INFO, MAIN, "creating window..");
    GLFWwindow* window = glfwCreateWindow(800, 600, "Shadematica", NULL, NULL);
    if (window == NULL)
    {
        log(ERROR, MAIN, "glfw could not initialize window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        log(ERROR, MAIN, "glad could not initialize");
        return -1;
    }

    Renderer renderer;
    renderer.init();
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // render
        renderer.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}