/*
- Car.hpp
-
- Author: 100086865
-
- Class that represents a car object. Provides functionallity for
- driving the car around the track.
*/

#pragma once

#include <glad\glad.h>
#include <glm\glm.hpp>

#include "GameObject.hpp"

class Car : public GameObject{
    
public:

    GLboolean boosting;
    GLfloat boostBar;
    GLboolean boostReady;
    GLfloat acceleration;
    GLfloat deceleration;
    GLfloat dx;
    GLfloat dy;

    /*
    - Default constructor
    */
    Car();

    /*
    - Sets the initial position, the size and the sprite of the Car object.
    - @param: Position
    - @param: Size
    - @param: Sprite
    */
    Car(glm::vec2 position, glm::vec2 size, Texture sprite);

    /*
    - Drives the card forward
    */
    void accelerate();

    /*
    - Drives the car backwards
    */
    void turnLeft();

    /*
    - Turns the car right
    */
    void turnRight();

    /*
    - Turns the car left
    */
    void reverse();
};