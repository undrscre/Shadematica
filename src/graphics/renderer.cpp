#include "renderer.h"
#include "shader.h"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

Renderer::Renderer(GLFWwindow* window, unsigned int width, unsigned int height) 
    : window(window), windowWidth(width), windowHeight(height), VAO(0), VBO(0), EBO(0), shader() {}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Renderer::init() {
    logm(INFO, RENDER, "attempting to initialize renderer...");

    float vertices[] = {
        -1.f, -1.f, 0.0f,
         1.f, -1.f, 0.0f,
         1.f,  1.f, 0.0f,
        -1.f,  1.f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    logm(INFO, RENDER, "renderer initialized");
}

void Renderer::render() {
    if (!shader.isCompiled()) {
        logm(WARN, RENDER, "shader is not compiled!");
        return;
    }
    shader.use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::update() {
    if (!shader.isCompiled()) {
        logm(WARN, RENDER, "shader is not compiled!");
        return;
    }
    float time = static_cast<float>(glfwGetTime());

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    glm::vec4 mouse(static_cast<float>(mouseX), static_cast<float>(mouseY), 0.0f, 0.0f);

    glm::vec2 resolution(windowWidth, windowHeight);

    shader.setFloat("iGlobalTime", time);
    shader.setVec3("iResolution", glm::vec3(resolution, resolution.x / resolution.y)); // Aspect ratio
    shader.setVec4("iMouse", mouse);

}

void Renderer::setShader(const Shader& shader) {
    this->shader = shader;
}
