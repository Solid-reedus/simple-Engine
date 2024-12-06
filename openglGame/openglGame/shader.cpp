#include "shader.h"
#include "string"
#include <fstream>
#include <sstream>
#include <iostream>
#include "glm/glm.hpp"


Shader::Shader(const char* p_vertexShaderDir, const char* p_fragmentShaderDir)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vShaderFile.open(p_vertexShaderDir);
        fShaderFile.open(p_fragmentShaderDir);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }


    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

}

void Shader::setBool(const std::string& p_name, bool p_namevalue) const
{
    glUniform1i(glGetUniformLocation(ID, p_name.c_str()), (int)p_namevalue);
}

void Shader::setInt(const std::string& p_name, int p_value) const
{
    glUniform1i(glGetUniformLocation(ID, p_name.c_str()), p_value);
}

void Shader::setFloat(const std::string& p_name, float p_value) const
{
    glUniform1f(glGetUniformLocation(ID, p_name.c_str()), p_value);
}

void Shader::setVec3(const std::string& p_name, const glm::vec3& p_value) const
{
    glUniform3fv(glGetUniformLocation(ID, p_name.c_str()), 1, &p_value[0]);
}
void Shader::setVec3(const std::string& p_name, float p_x, float p_y, float p_z) const
{
    glUniform3f(glGetUniformLocation(ID, p_name.c_str()), p_x, p_y, p_z);
}

void Shader::setMat4(const std::string& p_name, const glm::mat4& p_mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, p_name.c_str()), 1, GL_FALSE, &p_mat[0][0]);
}

