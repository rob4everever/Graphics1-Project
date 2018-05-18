/*
- GameObject.hpp
-
- Author: 100086865
-
- Source file for GameObject.hpp, contains function definitions.
*/

#include "GameObject.hpp"
#include "glm/gtx/string_cast.hpp"

GameObject::GameObject() : position(0, 0), size(1, 1), sprite(), colour(1.0f), angle(0.0f) { }

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture sprite, glm::vec3 color)
    : position(pos), size(size), sprite(sprite), colour(color), angle(0.0f) {
}

void GameObject::draw(SpriteRenderer &renderer) {
    renderer.drawSprite(this->sprite, this->position, this->size, this->angle, this->colour);
}