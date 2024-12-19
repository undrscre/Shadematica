#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "logger.h"
#include "graphics/shader.h"
#include "graphics/renderer.h"

int main()
{
    logm(INFO, MAIN, "Hello from Shadematica!");

    if (!glfwInit()) {
        logm(ERROR, MAIN, "glfw could not initialize");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    logm(INFO, MAIN, "creating window..");
    GLFWwindow* window = glfwCreateWindow(800, 600, "Shadematica", NULL, NULL);
    if (window == NULL)
    {
        logm(ERROR, MAIN, "glfw could not initialize window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        logm(ERROR, MAIN, "glad could not initialize");
        return -1;
    }

    // temporary! only for development
    std::ifstream vertexFile("src/graphics/shaders/meow.vert");
    std::ifstream fragmentFile("src/graphics/shaders/meow.frag");

    if (!vertexFile.is_open() || !fragmentFile.is_open()) {
        logm(ERROR, RENDER, "failed to open shader files");
        return -1;
    }

    std::stringstream vertexStream, fragmentStream;
    vertexStream << vertexFile.rdbuf();
    fragmentStream << fragmentFile.rdbuf();

    std::string vertexShaderSource = vertexStream.str();
    std::string fragmentShaderSource = fragmentStream.str();

    Shader shader(vertexShaderSource.c_str(), fragmentShaderSource.c_str());

    Renderer renderer(window, 800, 600);  // Window size: 800x600
    renderer.init();
    renderer.setShader(shader);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // render
        renderer.update();
        renderer.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}