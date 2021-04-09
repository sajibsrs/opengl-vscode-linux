#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

class Shader
{
public:
    unsigned int ID;

    Shader(const char *vertexPath, const char *fragmentPath)
    {
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vertexShaderFile;
        std::ifstream fragmentShaderFile;

        vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            vertexShaderFile.open(vertexPath);
            fragmentShaderFile.open(fragmentPath);

            std::stringstream vertexShaderStream, fragmentShaderStream;

            vertexShaderStream << vertexShaderFile.rdbuf();
            fragmentShaderStream << fragmentShaderFile.rdbuf();

            vertexShaderFile.close();
            fragmentShaderFile.close();

            vertexCode = vertexShaderStream.str();
            fragmentCode = fragmentShaderStream.str();
        }
        catch (std::ifstream::failure &e)
        {
            std::cout << "Error: Failed to read shader file" << std::endl;
        }

        const char *vertexShaderCode = vertexCode.c_str();
        const char *fragmentShaderCode = fragmentCode.c_str();

        unsigned int vertex, fragment;

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexShaderCode, NULL);
        glCompileShader(vertex);
        checkCompilerErrors(vertex, "vertex");

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
        glCompileShader(fragment);
        checkCompilerErrors(fragment, "fragment");

        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompilerErrors(ID, "program");

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    };

    void use()
    {
        glUseProgram(ID);
    };

    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    };

    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    };

    void setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    };

private:
    void checkCompilerErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];

        if (type != "program")
        {

            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "Error: Shader compilation error: " << type << "\n"
                          << infoLog << "\n -----" << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);

            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "Error: Shader linking error: " << type << "\n"
                          << infoLog << "\n -----" << std::endl;
            }
        }
    };
};

#endif