//
// Created by Marco Otero on 2/22/25.
//

#include "Shader.h"

std::string Shader::loadFromFile(const std::string& filePath) const
{
    std::ifstream shaderFile(filePath);
    if (!shaderFile.is_open()) {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << shaderFile.rdbuf();
    return buffer.str();
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
}

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
{
    // Load and compile shaders
    std::string vertexCode = loadFromFile(vertexPath);
    std::string fragmentCode = loadFromFile(fragmentPath);

    if (vertexCode.empty() || fragmentCode.empty()) {
        std::cerr << "Error: One or both shader files are empty!" << std::endl;
    }

    const char* vertexSource = vertexCode.c_str();
    const char* fragSource =fragmentCode.c_str();

    // Create Vertex Shader Object and get its reference
    //G Luint is just an unsigned int
    const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach Vertex Shader source to the Vertex Shader Object
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    // Compile the Vertex Shader into machine code
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader, "VERTEX");


    //Same thing for fragment shader object
    const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragSource, nullptr);
    glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, "FRAGMENT");

    // Create Shader Program Object and get its reference
    this->shaderID = glCreateProgram(); //private member variable
    // Attach the Vertex and Fragment Shaders to the Shader Program
    glAttachShader(this->shaderID, vertexShader);
    glAttachShader(this->shaderID, fragmentShader);
    // Wrap-up/Link all the shaders together into the Shader Program
    glLinkProgram(this->shaderID);
    checkCompileErrors(this->shaderID, "PROGRAM");

    // Delete the now useless Vertex and Fragment Shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

//DEBUGGING TESTED USED FROM CHATGPT
void Shader::checkCompileErrors(GLuint shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];

    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR: " << type << " SHADER COMPILATION FAILED\n" << infoLog << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR: SHADER PROGRAM LINKING FAILED\n" << infoLog << std::endl;
        }
    }
}

