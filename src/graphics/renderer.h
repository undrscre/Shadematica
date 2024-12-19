#ifndef RENDERER_H
#define RENDERER_H

#include "shader.h"  // only necessary for the function declarations
#include "../logger.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void init();
    void render();
    void update();
    void setShader(const Shader& shader);

private:
    unsigned int VAO, VBO, EBO;
    Shader shader;
};

#endif  // RENDERER_H
