/*
- TrackPiece.hpp
-
- Author: 100086865
-
- GameObject sub class that represents a single tile of a racetrack.
- Tile could be straights, turns, offroad, etc. These are stored in a vector
- in RaceTrack.cpp and drawn to the screen to produce a track.
*/

#pragma once

#include <glad\glad.h>
#include <glm\glm.hpp>
#include "GameObject.hpp"
#include "ResourceLoader.hpp"
#include "Texture.hpp"
#include "Coin.hpp"

class TrackPiece : public GameObject {

public:

    GLfloat friction;
    GLboolean haveCoin;
    
    TrackPiece(glm::vec2 pos, glm::vec2 size, Texture sprite, GLboolean haveCoin, GLfloat friction = 0.95f);
    Coin* generateCoin();
};