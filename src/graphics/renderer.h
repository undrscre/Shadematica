#ifndef RENDERER_H
#define REMDERER_H

#include "shader.h"

#include <glm/glm.hpp>
#include <GLFW/glfw3.h> 

class Renderer {
public:
    GLFWwindow* window;          
    unsigned int windowWidth, windowHeight;
    unsigned int VAO, VBO, EBO;
    Shader shader; 

    Renderer(GLFWwindow* window, unsigned int width, unsigned int height);
    ~Renderer();
    void init();
    void render();
    void update();

    void setShader(const Shader& shader);
};

#endif
