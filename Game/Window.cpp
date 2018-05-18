/*
- Window.cpp
-
- Author: 100086865
-
- Entry point for the game. Creates a window, initialises the
- game and keeps it updated in the game loop. Keyboard input
- is also captured and appropiately handled here.
*/

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <gl\GLU.h>

#include <iostream>

#include "Window.hpp"
#include "Game.hpp"
#include "ResourceLoader.hpp"

//Screen dimensions
const GLuint SCREEN_WIDTH = 1280;
const GLuint SCREEN_HEIGHT = 768;

//Game object
Game game(SCREEN_WIDTH, SCREEN_HEIGHT);

int main() {

    //GLFW initilisation code
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //GLFW window
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GameWithNoName", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    //GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Initialize game
    game.init();

    //DeltaTime variables
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;

    game.state = GAME_INTRO;

    //Game loop
    while (!glfwWindowShouldClose(window)) {

        //Calculate delta time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        //Manage user input
        game.processInput(deltaTime);

        //Update Game state
        game.update(deltaTime);

        //Render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        game.render();

        //Double Buffer
        glfwSwapBuffers(window);

        //Vsync
        glfwSwapInterval(1);
    }

    //Delete all resources as loaded using the resource manager
    ResourceLoader::clear();

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {

    //ESC: closes the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            game.keys[key] = GL_TRUE;
        }
        else if (action == GLFW_RELEASE) {
            game.keys[key] = GL_FALSE;
            game.keysProcessed[key] = GL_FALSE;
        }
    }
}