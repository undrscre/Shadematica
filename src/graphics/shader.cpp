#include "shader.h"
#include <glad/glad.h>
#include "../logger.h"

Shader::Shader() : ID(0), compiled(false) {}

Shader::Shader(const char* vertexCode, const char* fragmentCode) : compiled(false) {
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        logm(ERROR, SHADER, "VERTEX COMPILATION FAILED: ");
        std::cout << infoLog << std::endl;
        return;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        logm(ERROR, SHADER, "FRAGMENT COMPILATION FAILED: ");
        std::cout << infoLog << std::endl;
        return;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        logm(ERROR, RENDER, std::string("SHADER LINKING FAILED: ") + infoLog);
        return;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    compiled = true;
}

Shader::~Shader() {
    drop();
}

void Shader::use() {
    if (compiled) {
        glUseProgram(ID);
    }
}

void Shader::drop() {
    if (compiled) {
        glDeleteProgram(ID);
        compiled = false;
    }
}

bool Shader::isCompiled() {
    return compiled;
}

void Shader::setBool(const std::string& name, bool value) {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value) {
    glUniform2f(glGetUniformLocation(ID, name.c_str()), value.x, value.y);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w);
}
