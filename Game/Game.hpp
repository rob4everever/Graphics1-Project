/*
- Game.hpp
-
- Author: 100086865
-
- Contains the game class, which holds all the state
- and functionality related to the game itself. Provides
- methods for initialising, updating and rendering the game
= as well as dealing with keyboard input. GameState enum is also
- provided to deal with the different states the game may be in.
*/

#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "Car.hpp"
#include "Coin.hpp"

/*
- Represents all the possible states the game could be in
- GAME_ACTIVE: Game is in progress
- GAME_MENU: Player is in the games menu
- GAME_INTRO: The games start screen with instructions
- GAME_OVER: The games has finished
*/
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_INTRO,
    GAME_OVER
};

class Game {

public:

    //State the game is in
    GameState   state;

    //Array of keys
    GLboolean   keys[1024];

    //Window dimensions
    GLuint      width, height;

    //Keys already pressed
    GLboolean keysProcessed[1024];

    /*
    - Constructor that creates the game and sets its dimenstions,
    - aswell as setting the initial GameState
    - @param: Game window width
    - @param: Game window height
    */
    Game(GLuint width, GLuint height);

    /*
    - Game destructor
    */
    ~Game();

    /*
    - Initialises the game, loads shaders, textures, levels, objects etc
    */
    void init();

    /*
    - Processes keyboard input
    - @param: Delta time
    */
    void processInput(GLfloat deltaTime);

    /*
    - Updates the game each frame
    - @param: Delta time
    */
    void update(GLfloat deltaTime);

    /*
    - Renders the game to the screen
    */
    void render();

    /*
    - Checks if a vehicle goes outside the boundaries of the track
    - @return: True if vehicle is detected outside track boundaries
    */
    GLboolean checkBoundries(Car* vehicle);

    /*
    - Checks if a collision between two game objects takes place
    - @return: True if detected, false otherwise
    */
    GLboolean checkCollision(GameObject &a, GameObject &b);

    /*
    - Changes the starting point texture that shows the current lap
    - based on the current lap
    */
    void updateLapTexture();

    Coin* findNearestCoin(glm::vec2 p);
};