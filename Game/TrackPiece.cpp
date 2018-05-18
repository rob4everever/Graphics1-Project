/*
- TrackPiece.cpp
-
- Author: 100086865
-
- Source file for TrackPiece.hpp, contains function definitions.
*/

#include "TrackPiece.hpp"

TrackPiece::TrackPiece(glm::vec2 pos, glm::vec2 size, Texture sprite, GLboolean haveCoin, GLfloat friction) : GameObject(pos, size, sprite), friction(friction), haveCoin(haveCoin) {}

Coin* TrackPiece::generateCoin() {

    GLuint high = (this->position.x + 128) - 30;
    GLuint low = (this->position.x) + 30;
    GLuint highy = (this->position.y + 128) - 30;
    GLuint lowy = (this->position.y) + 30;

    GLfloat x = rand() % ((high - low) + 1) + low;
    GLfloat y = rand() % ((highy - lowy) + 1) + lowy;

    glm::vec2 coinPos = glm::vec2(x, y);
    ResourceLoader::loadTexture("textures/coin.png", GL_TRUE, "coin");
    Texture coinSprite = ResourceLoader::getTexture("coin");
    Coin* c = new Coin(coinPos, coinSprite);

    if (this->haveCoin) {
        return c;
    }
}