//
// Created by Nina on 2021/12/30.
//

#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "ball.h"
#include "background.h"
//#include "ball.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Game {
private:
    sf::RenderWindow* window;

    //Player
    Player* playerJie;
    Player* playerCMK;
    Ball* ball;
    Background* background;

    //Private Function
    void initWindow();
    void initPlayer();
    void initBall();
    void initBackground();

public:
    Game();
    ~Game() ;

    //Functions
    void run();
    void updatePlayer();
    void updateBallCollision();
//    void updateGravity();
    void updateBall();
    void update();
    void renderPlayer(sf::RenderTarget& target);
    void renderBall(sf::RenderTarget& target);
    void renderBackground(sf::RenderTarget &target);
//    void processKey();
    void render();



};
#endif //GAME_H
