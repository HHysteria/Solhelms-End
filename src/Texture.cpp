//
// Created by Marco Otero on 2/22/25.
//

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../External/stb_image.h"

Texture::~Texture() {
    glDeleteTextures(1, &textureID);
}

/* Might be used for textures of a different type
Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
    // Assigns the type of the texture ot the texture object
    type = texType;

    // Stores the width, height, and the number of color channels of the image
    int widthImg, heightImg, numColCh;
    // Flips the image so it appears right side up
    stbi_set_flip_vertically_on_load(true);
    // Reads the image from a file and stores it in bytes
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

    // Generates an OpenGL texture object
    glGenTextures(1, &this->textureID);
    // Assigns the texture to a Texture Unit
    glActiveTexture(slot);
    glBindTexture(texType, this->textureID);

    // Configures the type of algorithm that is used to make the image smaller or bigger
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Configures the way the texture repeats (if it does at all)
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Assigns the image to the OpenGL Texture object
    glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
    // Generates MipMaps
    glGenerateMipmap(texType);

    // Deletes the image data as it is already in the OpenGL Texture object
    stbi_image_free(bytes);

    // Unbinds the OpenGL Texture object so that it can't accidentally be modified
    glBindTexture(texType, 0);
}*/

Texture::Texture(const std::string& filepath) : textureID(0), width(0), height(0) {
    // Generate texture
    glGenTextures(1, &textureID);
    this->bind(); //bind texture

    // Load texture data
    stbi_set_flip_vertically_on_load(true); // Flip texture vertically (OpenGL expects textures upside down)
    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);
    if (data == nullptr) {
        std::cerr << "ERROR: Failed to load texture: " << filepath << std::endl;
        return;
    }

    // Upload texture data to GPU
    GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB; // Handle both RGB and RGBA textures
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Free image data
    stbi_image_free(data);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
/* used in different Texture constructor
void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
    // Gets the location of the uniform
    GLuint texUni = glGetUniformLocation(shader.getShaderID(), uniform);
    // Shader needs to be activated before changing the value of a uniform
    shader.use();
    // Sets the value of the uniform
    glUniform1i(texUni, unit);
}*/