//
// Created by Marco Otero on 2/22/25.
//

#include "Game.h"


Game::Game()
{
    initWindow(); // Initialize OpenGL context first
    initResources(); // Initialize shader and mesh after OpenGL context is ready and player
}


void Game::initWindow() {
    // Initialize GLFW
    glfwInit();
    // Tell GLFW what version of OpenGL we are using
    // In this case we are using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we are using the CORE profile
    // So that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Gets full screen values, all this is used in toggle fullscreen func
    this->monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    //Starts in windowed mode of 800x800
    this->window = glfwCreateWindow(this->windowedWidth, this->windowedHeight, "Solhem End", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Load GLAD
    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    // Set the viewport in windowed mode
    glViewport(0, 0, this->windowedWidth, this->windowedHeight);
}

void Game::initResources() {
    // Initialize shader and mesh after OpenGL context is ready
    //NOTE: TOTAL WIDTH OF PNG CANT BE LONGER THAN 16000 PIXELS, otherwise shit no load
    this->shader = std::make_unique<Shader>(RESOURCES_PATH "Shaders/default.vert",RESOURCES_PATH "Shaders/default.frag");
    this->player = std::make_unique<Player>(RESOURCES_PATH "_PNG/idleKnight.png",32,32,9,100);
}


void Game::toggleFullScreen()
{
    this->isFullscreen = !this->isFullscreen; //flips state of full screen bool

    if (this->isFullscreen) // check
    {
        // Save window position and size
        glfwGetWindowPos(this->window, &this->windowPosX, &this->windowPosY);
        glfwGetWindowSize(this->window, &this->windowedWidth, &this->windowedHeight);

        //Get window resolution
        const GLFWvidmode* mode = glfwGetVideoMode(this->monitor);
        glfwSetWindowMonitor(this->window,this->monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
    else //switch back to windowed mode
    {
        glfwSetWindowMonitor(this->window,nullptr,this->windowPosX,
            this->windowPosY,this->windowedWidth,this->windowedHeight,0);
    }
}

/*
 *
 * GAME LOOP FUNCTIONS
 *
 *
 *
 */


void Game::processInput(float deltaTime) const
{
    //IF Escape key pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    static bool fullScreenKeyPressed = false; //need to be static so if it is pressed it is stored in memory
    if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
    {
        if (fullScreenKeyPressed == false) //happens only once
        {
            const_cast<Game *>(this)->toggleFullScreen(); //changes to full screen
            fullScreenKeyPressed = true;     //change key and it is remembered into next function call
        }
        else
        {
            fullScreenKeyPressed = false;
        }
    }

    glm::vec2 movement{0.0f, 0.0f};
    if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS) {movement.y += 1.0f;}
    if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS) {movement.x -= 1.0f;}
    if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS) {movement.y -= 1.0f;}
    if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS) {movement.x += 1.0f;}

    // Normalize movement vector to ensure consistent speed
    if (glm::length(movement) > 0.0f) {
        movement = glm::normalize(movement);
    }
    // Update player position
    float speed = 0.5;
    movement.x = movement.x * deltaTime * speed;
    movement.y = movement.y * deltaTime * speed;
    this->player->move(movement); // Adjust speed as needed
}

void Game::run()
{
    /* IF NEED TO KNOW MAX TEXTURE SIZE
    GLint maxTextureSize;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
    std::cout << "Max texture size: " << maxTextureSize << std::endl;
    if (!this->window || !this->shader) {
        std::cerr << "Game is not properly initialized. Cannot run." << std::endl;
        return;
    }
    */
    //STUFF GETS RID OF BLACK BACKGROUND IN PNG MAKING TEXTURE TRANSPARENT
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    //Start in fullscreen
    toggleFullScreen();

    // Game Loop
    float lastFrameTime = 0.0;
    while (!glfwWindowShouldClose(this->window)) {
        // Calculate delta time
        float currentFrameTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        this->processInput(deltaTime);
        this->render();
        this->player->update(deltaTime);
    }
    this->cleanup();
}

void Game::render() const
{
    // Specify the color of the background, dark blue color
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT);

    // Tell OpenGL which Shader Program we want to use
    this->shader->use();
    this->player->render(*shader);

    //Changes buffers
    glfwSwapBuffers(window);
    // Take care of all GLFW events
    glfwPollEvents();
}


void Game::cleanup() const{
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
}



