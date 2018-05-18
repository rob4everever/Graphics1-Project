/*
- Coin.hpp
-
- Author: 100086865
-
- Game object sub class that represents a coin in the game.
- A coin is a collectable item which the player uses to increase
- his boost bar, once the bar is full a turbo boost is available.
*/

#pragma once

#include "GameObject.hpp"

class Coin : public GameObject {

public:
    //Value of a coin
    GLuint coinValue;

    //Determine if a coin is collected
    GLboolean isCollected;

    /*
    - Default constructor
    */
    Coin();

    /*
    - Creates a coin object
    - @param: Coin position
    - @param: Coin texture
    */
    Coin(glm::vec2 coinPosition, Texture sprite);
};