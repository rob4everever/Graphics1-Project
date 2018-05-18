/*
- RaceTrack.cpp
-
- Author: 100086865
-
- Source file for RaceTrack.hpp, contains function definitions.
*/

#include "RaceTrack.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

RaceTrack::RaceTrack(std::string levelFile) : levelFile(levelFile), tileSize(128.0f) {
    parseTrackCodes();
}

void RaceTrack::parseTrackCodes() {

    this->trackCodes.clear();

    GLuint trackCode;
    std::string line;
    std::ifstream fstream(this->levelFile);

    if (fstream) {

        while (std::getline(fstream, line)) {
            std::istringstream sstream(line);
            std::vector<GLuint> row;

            while (sstream >> trackCode) {
                row.push_back(trackCode);
            }

            trackCodes.push_back(row);
        }
    }

    generateLevel();
}

void RaceTrack::generateLevel() {

    //How many tiles accross and down
    GLuint rowLength = trackCodes[0].size();
    GLuint columnHeight = trackCodes.size();

    //Dimensions of the track
    this->width = rowLength * this->tileSize;
    this->height = columnHeight * this->tileSize;

    //Track Piece fields
    TrackPiece* trackPiece;
    glm::vec2 position = glm::vec2(0.0f, 0.0f);
    glm::vec2 size = glm::vec2(tileSize, tileSize);
    Texture sprite;

    //TrackPiece Textures
    ResourceLoader::loadTexture("textures/grass.png", GL_TRUE, "grass");
    ResourceLoader::loadTexture("textures/dirt.png", GL_TRUE, "dirt");
    ResourceLoader::loadTexture("textures/tree.png", GL_TRUE, "tree");
    ResourceLoader::loadTexture("textures/straight_vertical.png", GL_FALSE, "straight_vertical");
    ResourceLoader::loadTexture("textures/straight_horizontal.png", GL_FALSE, "straight_horizontal");
    ResourceLoader::loadTexture("textures/turn_up_left.png", GL_TRUE, "turn_up_left");
    ResourceLoader::loadTexture("textures/turn_up_right.png", GL_TRUE, "turn_up_right");
    ResourceLoader::loadTexture("textures/turn_down_left.png", GL_TRUE, "turn_down_left");
    ResourceLoader::loadTexture("textures/turn_down_right.png", GL_TRUE, "turn_down_right");
    ResourceLoader::loadTexture("textures/start.png", GL_TRUE, "start");

    //Background track piece for corners
    Texture grass = ResourceLoader::getTexture("dirt");
    Texture dirt = ResourceLoader::getTexture("grass");

    std::vector<TrackPiece*> row;

    for (int i = 0; i < columnHeight; i++) {

        row.clear();

        for (int j = 0; j < rowLength; j++) {

            if (trackCodes[i][j] == 0) {
                sprite = ResourceLoader::getTexture("grass");
                trackPiece = new TrackPiece(position, size, sprite, GL_FALSE, 0.85);
                row.push_back(trackPiece);
            }
            if (trackCodes[i][j] == 1) {
                sprite = ResourceLoader::getTexture("straight_horizontal");
                trackPiece = new TrackPiece(position, size, sprite, GL_TRUE);
                row.push_back(trackPiece);
            }
            if (trackCodes[i][j] == 2) {
                sprite = ResourceLoader::getTexture("straight_vertical");
                trackPiece = new TrackPiece(position, size, sprite, GL_TRUE);
                row.push_back(trackPiece);
            }
            if (trackCodes[i][j] == 3) {
                sprite = ResourceLoader::getTexture("turn_up_left");
                trackPiece = new TrackPiece(position, size, sprite, GL_TRUE);
                TrackPiece* bg = new TrackPiece(position, size, grass, GL_FALSE);
                row.push_back(bg);
                row.push_back(trackPiece);
            }
            if (trackCodes[i][j] == 4) {
                sprite = ResourceLoader::getTexture("turn_up_right");
                trackPiece = new TrackPiece(position, size, sprite, GL_TRUE);
                TrackPiece* bg = new TrackPiece(position, size, grass, GL_FALSE);
                row.push_back(bg);
                row.push_back(trackPiece);
            }
            if (trackCodes[i][j] == 5) {
                sprite = ResourceLoader::getTexture("turn_down_left");
                trackPiece = new TrackPiece(position, size, sprite, GL_TRUE);
                TrackPiece* bg = new TrackPiece(position, size, grass, GL_FALSE);
                row.push_back(bg);
                row.push_back(trackPiece);
            }
            if (trackCodes[i][j] == 6) {
                sprite = ResourceLoader::getTexture("turn_down_right");
                trackPiece = new TrackPiece(position, size, sprite, GL_TRUE);
                TrackPiece* bg = new TrackPiece(position, size, grass, GL_FALSE);
                row.push_back(bg);
                row.push_back(trackPiece);
            }
            if (trackCodes[i][j] == 7) {
                sprite = ResourceLoader::getTexture("start");
                trackPiece = new TrackPiece(position, size, sprite, GL_FALSE);
                row.push_back(trackPiece);
                this->startLine = position;
                this->startPiece = trackPiece;
            }
            if (trackCodes[i][j] == 8) {
                sprite = ResourceLoader::getTexture("dirt");
                trackPiece = new TrackPiece(position, size, sprite, GL_FALSE, 0.85);
                row.push_back(trackPiece);
            }
            if (trackCodes[i][j] == 9) {
                sprite = ResourceLoader::getTexture("tree");
                trackPiece = new TrackPiece(position, size, sprite, GL_FALSE, 0.85);
                TrackPiece* bg = new TrackPiece(position, size, grass, GL_FALSE, 0.85);
                row.push_back(bg);
                row.push_back(trackPiece);
            }

            //Increment along the X axis
            position = position + glm::vec2(tileSize, 0.0);
        }

        //Add row to trackpieces vector
        this->trackPieces.push_back(row);

        //Increment along the y axis
        GLint currentX = position.x;
        position = position + glm::vec2(-currentX, tileSize);
    }
}

void RaceTrack::generateCoins(SpriteRenderer &renderer) {

    coins.clear();

    for (std::vector<TrackPiece*> s : this->trackPieces) {

        for (TrackPiece *p : s) {

            if (p->haveCoin == GL_TRUE) {
                coins.push_back(p->generateCoin());
            }
        }
    }
}

void RaceTrack::draw(SpriteRenderer &renderer) {

    for (std::vector<TrackPiece*> s : trackPieces) {

        for (TrackPiece *p : s) {

            p->draw(renderer);
        }
    }

    for (Coin* c : coins) {
        
        if (!c->isCollected) {
            c->draw(renderer);
        }
    }
}

