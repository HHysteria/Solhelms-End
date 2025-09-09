//
// Created by Marco Otero on 2/22/25.
//

#ifndef GAME_H
#define GAME_H

#include "Sprite.h"

using std::vector;


class Game {
private:
    //Window and shader/mesh ptrs have to be pointers cuz their constructors require parameters that are loaded later
    GLFWwindow* window;
    std::unique_ptr<Shader> shader;

    //Called in constructor
    void initWindow();
    void initResources();

    //Window functions used in run(), specifically game loop
    void processInput(float deltaTime) const;
    //void update();
    void render() const;

    //Called after game loop to destroy stuff
    void cleanup() const;

    // Make fullscreen
    GLFWmonitor* monitor = nullptr; //called in init and is set to full screen values
    //Window values for default view 800x600
    bool isFullscreen = false;
    int windowedWidth = 800, windowedHeight = 600; // Default size
    int windowPosX = 100, windowPosY = 100;

    //Game entities and stuff
    std::unique_ptr<Player> player;

public:
    Game();
    void run();
    void toggleFullScreen();
};



#endif //GAME_H
