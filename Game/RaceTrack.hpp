/*
- RaceTrack.hpp
-
- Author: 100086865
-
- Class that represents a race track for the game.
*/

#pragma once

#include <glad\glad.h>
#include <glm\glm.hpp>

#include <vector>

#include "SpriteRenderer.hpp"
#include "Texture.hpp"
#include "ResourceLoader.hpp"
#include "TrackPiece.hpp"

class RaceTrack {

public:

    //Level dimensions
    GLuint width, height;

    //Text file that contains a track layout
    std::string levelFile;

    //Numerical codes that represent different pieces of a track
    std::vector<std::vector<GLuint>> trackCodes;

    //Vector that contains a vector of rows of trackpieces
    std::vector<std::vector<TrackPiece*>> trackPieces;

    //Vector that contains the locations of all coins on a track
    std::vector<Coin*> coins;

    //Size of a single tile
    GLfloat tileSize;

    //Starting position of a track
    glm::vec2 startLine;

    TrackPiece* startPiece;
    TrackPiece* insPiece;

    /*
    - RaceTrack constructor that provides a level file and calls the parseTrackCodes
    - function
    */
    RaceTrack(std::string levelFile);

    /*
    - Parses the level text file to get the track piece codes
    - and stores them in the trackCodes vector. After that, the generateLevel
    - function is called so the level can be built.
    */
    void parseTrackCodes();

    /*
    - Generates the track pieces based on the set of track codes and
    - stores them in the trackPieces vector
    */
    void generateLevel();

    void generateCoins(SpriteRenderer &renderer);



    /*
    - Draws the track pieces in trackPieces to the screen
    - @param: SpriteRenderer
    */
    void draw(SpriteRenderer &renderer);



};