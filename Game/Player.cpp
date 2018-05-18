/*
- Player.cpp
-
- Author: 100086865
-
- Source file for Player.hpp, contains function definitions.
*/

#include "Player.hpp"

Player::Player(Car *car) : car(*car), coinsCollected(0), currentPosition(1), currentLap(1) {}

GLuint Player::getCoinsCollected() {
    return this->coinsCollected;
}

GLuint Player::getCurrentPosition() {
    return this->currentPosition;
}

GLuint Player::getCurrentLap() {
    return this->currentLap;
}