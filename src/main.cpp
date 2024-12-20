#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "logger.h"
#include "graphics/shader.h"
#include "graphics/renderer.h"

// todo: put this somewhere else
const char *vertexFallback = "#version 330 core\n"
                            "layout (location = 0) in vec3 aPos;\n"
                            "void main()\n"
                            "{\n"
                            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                            "}\0";

const char *fragmentFallback = "#version 330 core\n"
                                "out vec4 FragColor;\n"
                                "uniform float iGlobalTime;\n"
                                "uniform vec3 iResolution;\n"
                                "void main()\n"
                                "{\n"
                                "    vec2 uv = gl_FragCoord.xy / iResolution.xy;\n"
                                "    vec3 color = vec3(uv.x, uv.y, sin(iGlobalTime) + 0.5);\n"
                                "    FragColor = vec4(color, 1.0);\n"
                                "}\0";

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

    Renderer renderer(window, 800, 600);  // Window size: 800x600

    std::ifstream vertexFile("src/graphics/shaders/meow.vert");
    std::ifstream fragmentFile("src/graphics/shaders/meow.frag");

    if (!vertexFile.is_open() || !fragmentFile.is_open()) {
        logm(ERROR, RENDER, "failed to open shader files, attempting fallback");
        return -1;
    }

    std::stringstream vertexStream, fragmentStream;
    vertexStream << vertexFile.rdbuf();
    fragmentStream << fragmentFile.rdbuf();

    std::string vertexShaderSource = vertexStream.str();
    std::string fragmentShaderSource = fragmentStream.str();

    Shader shader(vertexShaderSource.c_str(), fragmentShaderSource.c_str());

    if (!shader.isCompiled()) {
        logm(WARN, RENDER, "shader cannot compile! attempting fallback");
        shader.drop();
        Shader fallback(vertexFallback, fragmentFallback);
        if (!fallback.isCompiled()) {
            logm(ERROR, RENDER, "fallback shader cannot compile! exiting");
            return -1;
        };
        logm(WARN, RENDER, "fallback compiled, using fallback..");
        fallback.use();
        renderer.setShader(fallback);
    } else {
        renderer.setShader(shader);
    }

    renderer.init();

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