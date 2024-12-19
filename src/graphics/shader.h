#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../logger.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

using namespace std;

class Shader {
public:
    unsigned int ID;
    bool compiled;

    Shader() : ID(0), compiled(false) {}

    Shader(const char* vertexCode, const char* fragmentCode) : compiled(false) {
        unsigned int vertex, fragment;
        int success;
        char infoLog[512];

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexCode, NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            string errorLog = "VERTEX COMPILATION FAILED: " + string(infoLog);
            logm(ERROR, RENDER, errorLog);
            return;
        }

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentCode, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            string errorLog = "FRAGMENT COMPILATION FAILED: " + string(infoLog);
            logm(ERROR, RENDER, errorLog);
            return;
        }

        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            string errorLog = "SHADER LINKING FAILED: " + string(infoLog);
            logm(ERROR, RENDER, errorLog);
            return;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);
        compiled = true;
    }

    void use() {
        if (compiled) {
            glUseProgram(ID);
        }
    }

    void drop() {
        glDeleteProgram(ID);
        compiled = false;
    }

    bool isCompiled() const {
        return compiled;
    }

    void setBool(const string& name, bool value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    void setInt(const string& name, int value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setFloat(const string& name, float value) const {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setVec2(const string& name, const glm::vec2& value) const {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), value.x, value.y);
    }

    void setVec3(const string& name, const glm::vec3& value) const {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
    }

    void setVec4(const string& name, const glm::vec4& value) const {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w);
    }
};

#endif
