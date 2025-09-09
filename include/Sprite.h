//
// Created by Marco Otero on 2/22/25.
//

#ifndef SPRITE_H
#define SPRITE_H

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include <../External/glm/glm.hpp>


class Sprite {
protected:
    std::unique_ptr<Texture> texture;
    std::unique_ptr<Mesh> mesh;
    glm::vec2 position; //will be initialized to center of screen (0,0)
    int frameWidth, frameHeight, frameCount;
    int currentFrame;
    float frameTime;
    float animationTimer;

public:
    //Texture path will be to sprite sheet
    Sprite(const std::string& texturePath, int frameWidth, int frameHeight, int frameCount);


    void setPosition(glm::vec2 position) {this->position = position;};
    //void setRotation(float rotation);
    void move(glm::vec2& movement);

    void update(float deltaTime);
    void updateMesh();
    void updateAnimation(float deltaTime);


    void render(Shader &shader);
};

class Player : public Sprite {
private:
    int health;
public:
    Player(const std::string& texturePath, int frameWidth, int frameHeight, int frameCount, int health)
        : Sprite(texturePath, frameWidth, frameHeight, frameCount), health(health) {};
};

#endif //SPRITE_H
