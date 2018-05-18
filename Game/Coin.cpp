/*
- Coin.cpp
-
- Author: 100086865
-
- Source file for Coin.hpp, contains function definitions.
*/

#include "Coin.hpp"

Coin::Coin() : GameObject(){}

Coin::Coin(glm::vec2 coinPosition, Texture sprite) : GameObject(coinPosition, glm::vec2(20, 20), sprite), isCollected(GL_FALSE), coinValue(10) {}