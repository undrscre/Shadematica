#include "renderer.h"
#include "shader.h" // You only need to include this here
#include <iostream>

Renderer::Renderer() : VAO(0), VBO(0), EBO(0), shader() {}

Renderer::~Renderer() {
    // Cleanup OpenGL resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Renderer::init() {
    log(INFO, RENDER, "attempting to initialize renderer...");

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

    // temporary! only for development
    std::ifstream vertexFile("src/graphics/shaders/meow.vert");
    std::ifstream fragmentFile("src/graphics/shaders/meow.frag");

    if (!vertexFile.is_open() || !fragmentFile.is_open()) {
        log(ERROR, RENDER, "failed to open shader files");
        return;
    }

    std::stringstream vertexStream, fragmentStream;
    vertexStream << vertexFile.rdbuf();
    fragmentStream << fragmentFile.rdbuf();

    std::string vertexShaderSource = vertexStream.str();
    std::string fragmentShaderSource = fragmentStream.str();

    shader = Shader(vertexShaderSource.c_str(), fragmentShaderSource.c_str());
    shader.use();

    log(INFO, RENDER, "renderer initialized");
}

void Renderer::render() {
    shader.use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::update() {
    // todo: update logic
}

void Renderer::setShader(const Shader& shader) {
    this->shader = shader;
}
