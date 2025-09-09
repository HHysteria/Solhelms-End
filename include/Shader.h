//
// Created by Marco Otero on 2/22/25.
//

#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <../External/glm/gtc/matrix_transform.hpp>  // Contains glm::translate, glm::rotate, glm::scale
#include <../External/glm/gtc/type_ptr.hpp>          // For passing matrices to shaders

class Shader {
private:
    GLuint shaderID;
    std::string loadFromFile(const std::string& filePath) const;
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader() {glDeleteProgram(this->shaderID);}

    GLuint getShaderID() const { return this->shaderID; }

    //Uses shader program compiled in shader constructor
    void use() const {glUseProgram(shaderID);}
    void setInt(const std::string& name, int value) const;
    void checkCompileErrors(GLuint shader, std::string type);
    void setMat4(const std::string& name, const glm::mat4& mat) const;
};



#endif //SHADER_H
