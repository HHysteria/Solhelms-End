//
// Created by Marco Otero on 2/22/25.
//

#ifndef TEXTURE_H
#define TEXTURE_H
#include <glad/glad.h>
#include <vector>
#include <iostream>
#include "Shader.h"

class Texture {
private:
    GLuint textureID;
    int width, height, nrChannels;


public:
    Texture(const std::string& filepath);
    ~Texture();

    GLenum type;
    //Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

    int getWidth() const { return width; }
    int getHeight() const { return height; }


    void bind() const {glBindTexture(GL_TEXTURE_2D, this->textureID);
    } //bind texture making it active

    // Assigns a texture unit to a texture
    //void texUnit(Shader& shader, const char* uniform, GLuint unit);
};



#endif //TEXTURE_H
