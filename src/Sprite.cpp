//
// Created by Marco Otero on 2/22/25.
//

#include "Sprite.h"

Sprite::Sprite(const std::string& texturePath, int frameWidth, int frameHeight, int frameCount)
    : position(glm::vec2(0, 0)), frameWidth(frameWidth), frameHeight(frameHeight), frameCount(frameCount), currentFrame(0), frameTime(0.15),
      animationTimer(0.0)
{
    this->texture = std::make_unique<Texture>(texturePath);

    // Calculate aspect ratio
    float aspectRatio = static_cast<float>(frameWidth) / static_cast<float>(frameHeight);

    // Is used
    // Adjust quad vertices to match the aspect ratio
    float quadWidth = 0.05f; // Base width (adjust as needed)
    float quadHeight = quadWidth / aspectRatio; // Height adjusted for aspect ratio

    // Define vertices for the quad
    std::vector<float> vertices = {
        // Positions          // Texture Coords
        -quadWidth, -quadHeight, 0.0,  0.0, 0.0,  // Bottom-left
         quadWidth, -quadHeight, 0.0,  1.0, 0.0,  // Bottom-right
         quadWidth,  quadHeight, 0.0,  1.0, 1.0,  // Top-right
        -quadWidth,  quadHeight, 0.0,  0.0, 1.0   // Top-left
    };

    // Define indices for the quad
    std::vector<GLuint> indices = {
        0, 1, 2,  // First triangle
        2, 3, 0   // Second triangle
    };

    // Create the mesh
    mesh = std::make_unique<Mesh>(vertices, indices);
}


void Sprite::render(Shader& shader) {
    // Bind the texture to texture unit 0
    glActiveTexture(GL_TEXTURE0); // Activate texture unit 0
    this->texture->bind();        // Bind the texture to the active texture unit

    // Set the texture sampler uniform
    shader.use();
    shader.setInt("texture1", 0); // Tell the shader to use texture unit 0

    //
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    shader.setMat4("model", model);

    // Render the mesh
    this->mesh->render();
}

void Sprite::move(glm::vec2& movement)
{
    this->position += movement;
}

void Sprite::update(float deltaTime) {
    this->updateAnimation(deltaTime); //has to be called before updateMesh cuz current frame changes
    this->updateMesh();
}

void Sprite::updateAnimation(float deltaTime) {
    this->animationTimer += deltaTime;                  //add elapsed time to animation timer
    if (this->animationTimer >= this->frameTime) {      //if enough time has passed
        this->animationTimer = 0.0f;                          // Reset the timer
        this->currentFrame = (this->currentFrame + 1) % this->frameCount; // Advance to the next frame,
                                                        //limit the value of currentFrame to a valid frame index by &
    }
}

void Sprite::updateMesh() {
    // Calculate texture coordinates for the current frame
    const float texX = static_cast<float>(currentFrame) / static_cast<float>(frameCount);  // Current frame's left edge
    const float texWidth = 1.0 / static_cast<float>(frameCount);  // Width of one frame

    //Needed to not appear stretched in actual window
    // Calculate aspect ratio
    //if divide quadHeight by 2 it looks better, idk why tho just do it trust
    float aspectRatio = static_cast<float>(frameWidth) / static_cast<float>(frameHeight) / 2;

    // Adjust quad vertices to match the aspect ratio
    //change width to adjust size;

    float quadWidth = 0.05f; // Base width (adjust as needed)
    float quadHeight = quadWidth / aspectRatio; // Height adjusted for aspect ratio

    // Update the mesh's vertices with new texture coordinates
    const std::vector<float> vertices = {
        // Positions          // Texture Coords
        -quadWidth, -quadHeight, 0.0,  texX, 0.0,  // Bottom-left
         quadWidth, -quadHeight, 0.0,  texX + texWidth, 0.0,  // Bottom-right
         quadWidth,  quadHeight, 0.0,  texX + texWidth, 1.0,  // Top-right
        -quadWidth,  quadHeight, 0.0,  texX, 1.0   // Top-left
    };

    // Update the mesh's vertices
    this->mesh->loadVertices(vertices);
}