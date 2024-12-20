#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <iostream>

#include "../logger.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader {
public:
    unsigned int ID;
    bool compiled;

    Shader(); 
    Shader(const char* vertexCode, const char* fragmentCode); 
    ~Shader(); 

    void use();
    void drop();
    bool isCompiled();

    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setVec2(const std::string& name, const glm::vec2& value);
    void setVec3(const std::string& name, const glm::vec3& value);
    void setVec4(const std::string& name, const glm::vec4& value);
};

#endif
