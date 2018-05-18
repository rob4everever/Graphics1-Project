/*
- Car.cpp
-
- Author: 100086865
-
- Source file for Car.hpp, contains function definitions.
*/

#include "Car.hpp"

Car::Car() : GameObject() {}

Car::Car(glm::vec2 position, glm::vec2 size, Texture sprite) : GameObject(position, size, sprite), dx(0), dy(0), acceleration(1.0f), deceleration(1.0f), boostBar(0), boostReady(GL_FALSE) {}

void Car::accelerate() {
    GLfloat cdx = sinf(this->angle) * this->acceleration*0.2;
    GLfloat cdy = -cosf(this->angle) * this->acceleration*0.2;
    this->dx += cdx;
    this->dy += cdy;
}

void Car::turnLeft() {
    this->angle -= 0.06f;
}

void Car::turnRight() {
    this->angle += 0.06f;
}

void Car::reverse() {
    GLfloat cdx = sinf(this->angle) * this->deceleration*0.1;
    GLfloat cdy = -cosf(this->angle) * this->deceleration *0.1;
    this->dx += -cdx;
    this->dy += -cdy;
}
