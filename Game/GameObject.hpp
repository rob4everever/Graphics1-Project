/*
- GameObject.hpp
-
- Author: 100086865
-
- Represents a single, generic game object. Used as a
- superclass for various game objects such as coins.
*/

#pragma once

#include <glad\glad.h>
#include <glm\glm.hpp>

#include "Texture.hpp"
#include "SpriteRenderer.hpp"

class GameObject {

public:

    //Object State
    glm::vec2 position;
    glm::vec2 size;
    Texture sprite;
    glm::vec3 colour;
    GLfloat angle;

    /*
    - Default constructor
    */
    GameObject();

    /*
    - Sets the fields of a game object
    - @param: Position
    - @param: Size
    - @param: Texture
    - @param: Colour
    */
    GameObject(glm::vec2 pos, glm::vec2 size, Texture sprite, glm::vec3 colour = glm::vec3(1.0f));

    /*
    - Draws a game object
    - @param: Renderer
    */
    virtual void draw(SpriteRenderer &renderer);
};