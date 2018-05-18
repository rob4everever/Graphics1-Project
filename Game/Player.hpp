/*
- Player.hpp
-
- Author: 100086865
-
- Player class. Assigns a player a car and has fields for
- the state of a current players game such as score, current lap
- and position.
*/

#pragma once

#include <glad\glad.h>

#include "Car.hpp"

class Player {

public:

    //Player state
    GLuint coinsCollected;
    GLuint currentPosition;
    GLuint currentLap;
    Car    car;

    /*
    - Constructor that assigns a car to a player and sets the
    - initial player fields.
    - @param: Car
    */
    Player(Car *car);

    /*
    - Returns the amount of coins a player ahs collected
    - @return: Amount of collected coins
    */
    GLuint getCoinsCollected();

    /*
    - Returns the players current position
    - @return: Current position
    */
    GLuint getCurrentPosition();

    /*
    - Returns the players current lap
    - @return: Current lap
    */
    GLuint getCurrentLap();
};