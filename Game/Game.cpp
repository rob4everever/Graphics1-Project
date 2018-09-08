/*
- Game.cpp
-
- Author: 100086865
-
- Source file for Game.hpp, contains function definitions.
*/

#include <math.h>
#include <irklang/irrKlang.h>

#include "Game.hpp"
#include "ResourceLoader.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "SpriteRenderer.hpp"
#include "Car.hpp"
#include "RaceTrack.hpp"
#include "Player.hpp"
#include "Coin.hpp"

using namespace irrklang;

//Game Objects
SpriteRenderer *renderer;
Car *car;
Car *AIcar;
RaceTrack *track;
Player *player;
ISoundEngine *SoundEngine = createIrrKlangDevice();

//Projection matrix
glm::mat4 projection;
glm::mat4 view;

//Track container
std::vector<RaceTrack*> tracks;
GLuint trackID = 0;

//Time variables
Coin* nearestCoin;

Game::Game(GLuint width, GLuint height) : width(width), height(height), state(GAME_ACTIVE), keys() {}

Game::~Game() {}

void Game::init() {

    //Load shaders
    ResourceLoader::loadShader("shaders/sprite.vert", "shaders/sprite.frag", nullptr, "sprite");

    //Configure shaders and set initial view
    projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
    view = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
    ResourceLoader::getShader("sprite").use().setInteger("image", 0);
    ResourceLoader::getShader("sprite").setMatrix4("projection", projection);
    ResourceLoader::getShader("sprite").setMatrix4("view", view);

    //Load textures
    ResourceLoader::loadTexture("textures/car1.png", GL_TRUE, "car1");
    ResourceLoader::loadTexture("textures/car2.png", GL_TRUE, "car2");
    ResourceLoader::loadTexture("textures/instructions.png", GL_TRUE, "instructions");
    ResourceLoader::loadTexture("textures/win_screen.png", GL_TRUE, "win");
    ResourceLoader::loadTexture("textures/loss_screen.png", GL_TRUE, "loose");

    //Set up renderer
    Shader s = ResourceLoader::getShader("sprite");
    renderer = new SpriteRenderer(s);

    //Audio
    SoundEngine->play2D("audio/bgmusic.mp3", GL_TRUE);
    SoundEngine->setSoundVolume(0.5);

    //Create level (put this in a loop)
    tracks.push_back(new RaceTrack("levels/one.lvl"));
    tracks.push_back(new RaceTrack("levels/two.lvl"));
    tracks.push_back(new RaceTrack("levels/three.lvl"));
    track = tracks[0];

    //Create car
    Texture carTexture = ResourceLoader::getTexture("car1");
    car = new Car(track->startLine, glm::vec2(20, 30), carTexture);

    Texture aiCarTexture = ResourceLoader::getTexture("car2");
    glm::vec2 AIstartPos = glm::vec2((track->startLine.x + 128.0f - 20), track->startLine.y);
    AIcar = new Car(AIstartPos, glm::vec2(20, 30), aiCarTexture);

    //Create player and assign a car
    player = new Player(car);
}

void Game::processInput(GLfloat deltaTime) {

    //Game keys
    if (this->state == GAME_ACTIVE) {

        if (this->keys[GLFW_KEY_W]) {
            car->accelerate();
        }

        if (this->keys[GLFW_KEY_A]) {
            car->turnLeft();
        }

        if (this->keys[GLFW_KEY_D]) {
            car->angle += 0.06f;
        }

        if (this->keys[GLFW_KEY_S]) {
            car->reverse();
        }
    }

    if (this->state == GAME_MENU) {
        
        if (this->keys[GLFW_KEY_ENTER] && !this->keysProcessed[GLFW_KEY_ENTER]) {
            this->state = GAME_ACTIVE;
            car->position = track->startLine;
            Texture aiCarTexture = ResourceLoader::getTexture("car2");
            glm::vec2 AIstartPos = glm::vec2((track->startLine.x + 128.0f - 20), track->startLine.y);
            AIcar->position = AIstartPos;
            track->generateCoins(*renderer);
            this->keysProcessed[GLFW_KEY_ENTER] = GL_TRUE;
        }

        if (this->keys[GLFW_KEY_A] && !this->keysProcessed[GLFW_KEY_A]) {
            if (trackID == 0) {
                trackID = tracks.size() - 1;
            }
            else {
                trackID--;
            }
            track = tracks[trackID];
            this->keysProcessed[GLFW_KEY_A] = GL_TRUE;
        }

        if (this->keys[GLFW_KEY_D] && !this->keysProcessed[GLFW_KEY_D]) {
            if (trackID == tracks.size() - 1) {
                trackID = 0;
            }
            else {
                trackID++;
            }
            track = tracks[trackID];
            this->keysProcessed[GLFW_KEY_D] = GL_TRUE;
        }
    }

    if (this->state == GAME_INTRO) {

        if (this->keys[GLFW_KEY_SPACE]) {
            this->state = GAME_MENU;
        }
    }

    if (this->state == GAME_OVER) {

        if (this->keys[GLFW_KEY_SPACE]) {
            this->state = GAME_MENU;
        }
    }
}

void Game::update(GLfloat deltaTime) {

    if (this->state == GAME_ACTIVE) {

        nearestCoin = findNearestCoin(AIcar->position);
        glm::vec2 to = nearestCoin->position - AIcar->position;
        to *= AIcar->acceleration * deltaTime;
        AIcar->position += to;

        //Zoom in after level is selected
        projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width / 1.5), static_cast<GLfloat>(this->height / 1.5), 0.0f, -1.0f, 1.0f);
        ResourceLoader::getShader("sprite").setMatrix4("projection", projection);

        //Update camera position
        GLfloat cameraX = -car->position.x + this->width / 2 - 200;
        GLfloat cameraY = -car->position.y + this->height / 2 - 200;
        glm::mat4 view = glm::translate(glm::mat4(), glm::vec3(cameraX, cameraY, 0.0f));
        ResourceLoader::getShader("sprite").setMatrix4("view", view);

        //Gets the tile that the car is currently in
        GLuint carTileX = car->position.x / 128;
        GLuint carTileY = car->position.y / 128;
        glm::vec2 currentCarPosition = glm::vec2(carTileX, carTileY);

        //Determine which part of the track the car is on and use that pieces friction
        car->position.x += car->dx;
        car->position.y += car->dy;
        car->dx *= track->trackPieces[carTileY][carTileX]->friction;
        car->dy *= track->trackPieces[carTileY][carTileX]->friction;
 
        //Check if the vehicle is going out of bounds, and rotate it back towards the track if so
        if (!checkBoundries(car)) {
            car->angle += 0.2;
            car->dx *= -1;
            car->dy *= -1;
            SoundEngine->play2D("audio/wallcrash.wav", GL_FALSE);
        }

        //Car collects a coin when it drives over it and increases boost bar
        for (Coin* coin : track->coins) {
            if (!coin->isCollected) {
                if (checkCollision(*car, *coin) || checkCollision(*AIcar, *coin)) {
                    coin->isCollected = GL_TRUE;
                    player->coinsCollected++;
                    SoundEngine->play2D("audio/coincollect.wav", GL_FALSE);
                }
            }
        }

        if (checkCollision(*car, *AIcar)) {
            car->angle += 0.2;
            car->dx *= -2;
            car->dy *= -2;
            SoundEngine->play2D("audio/carcrash.wav", GL_FALSE);
        }

        //Check if a player crosses the start line with all coins collected
        if ((currentCarPosition.x == track->startLine.x / 128) && (currentCarPosition.y == track->startLine.y / 128) && (player->coinsCollected == track->coins.size())) {
            player->currentLap++;
            player->coinsCollected = 0;
            track->generateCoins(*renderer);
            updateLapTexture();
            SoundEngine->play2D("audio/lap.wav", GL_FALSE);
        }

        //Check if player has completed all laps
        if (player->currentLap > 3) {
            player->currentLap = 1;
            updateLapTexture();
            this->state = GAME_OVER;
        }
    }
}

void Game::render() {

    if (this->state == GAME_ACTIVE) {
        track->draw(*renderer);
        car->draw(*renderer);
        AIcar->draw(*renderer);
    }

    if (this->state == GAME_MENU) {
        projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
        view = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
        ResourceLoader::getShader("sprite").use().setInteger("image", 0);
        ResourceLoader::getShader("sprite").setMatrix4("projection", projection);
        ResourceLoader::getShader("sprite").setMatrix4("view", view);
        track->draw(*renderer);
    }

    if (this->state == GAME_INTRO) {
        projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
        view = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
        ResourceLoader::getShader("sprite").use().setInteger("image", 0);
        ResourceLoader::getShader("sprite").setMatrix4("projection", projection);
        ResourceLoader::getShader("sprite").setMatrix4("view", view);
        Texture t = ResourceLoader::getTexture("instructions");
        TrackPiece *p = new TrackPiece(glm::vec2(0, 0), glm::vec2(this->width, this->height), t, GL_FALSE);
        p->draw(*renderer);
    }

    if (this->state == GAME_OVER) {
        projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
        view = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
        ResourceLoader::getShader("sprite").use().setInteger("image", 0);
        ResourceLoader::getShader("sprite").setMatrix4("projection", projection);
        ResourceLoader::getShader("sprite").setMatrix4("view", view);
        Texture t = ResourceLoader::getTexture("win");
        TrackPiece *p = new TrackPiece(glm::vec2(0, 0), glm::vec2(this->width, this->height), t, GL_FALSE);
        p->draw(*renderer);
    }
}

GLboolean Game::checkBoundries(Car* vehicle) {

    if ((vehicle->position.x > 0) && (vehicle->position.x < track->width - vehicle->size.x) && (vehicle->position.y > 0) &&
        (vehicle->position.y < track->height - vehicle->size.y)) {
        return true;
    }
    else {
        return false;
    }
}

GLboolean Game::checkCollision(GameObject &a, GameObject &b) {
    //X-axis collision
    GLboolean collisionX = a.position.x + a.size.x >= b.position.x && b.position.x + b.size.x >= a.position.x;
    //Y-axis collision
    GLboolean collisionY = a.position.y + a.size.y >= b.position.y && b.position.y + b.size.y >= a.position.y;
    return collisionX && collisionY;
}

void Game::updateLapTexture() {

    ResourceLoader::loadTexture("textures/start.png", GL_TRUE, "start1");
    ResourceLoader::loadTexture("textures/start_2.png", GL_TRUE, "start2");
    ResourceLoader::loadTexture("textures/start_3.png", GL_TRUE, "start3");
    Texture start1 = ResourceLoader::getTexture("start1");
    Texture start2 = ResourceLoader::getTexture("start2");
    Texture start3 = ResourceLoader::getTexture("start3");

    if (player->currentLap == 1) {
        track->startPiece->sprite = start1;
    }

    if (player->currentLap == 2) {
        track->startPiece->sprite = start2;
    }

    if (player->currentLap == 3) {
        track->startPiece->sprite = start3;
    }
}

Coin* Game::findNearestCoin(glm::vec2 p){

    GLfloat cpx = p.x;
    GLfloat cpy = p.y;
    nearestCoin = track->coins[0];

    for (Coin* c : track->coins) {

        if (!c->isCollected) {

            GLfloat coinposx = c->position.x;
            GLfloat coinposy = c->position.y;
            GLfloat distanceBetweenCarAndCoin = sqrt(pow(cpx - coinposx, 2) + pow(cpy - coinposy, 2));
            GLfloat distanceBetweenCarAndCurrentNearestCoin = sqrt(pow(cpx - nearestCoin->position.y, 2) + pow(nearestCoin->position.x - cpy, 2));

            if (distanceBetweenCarAndCoin < distanceBetweenCarAndCurrentNearestCoin) {
                nearestCoin = c;
            }
        }
    }
    return nearestCoin;
}