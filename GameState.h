#ifndef PD110_1_FP_GAMESTATE_H
#define PD110_1_FP_GAMESTATE_H

#include "State.h"
#include "player.h"
#include "ball.h"
#include "Enemies.h"

class GameState: public State{
private:
    // character
    Player* playerJie;
    Player* playerCMK;

    // background
    sf::Sprite sprite;
    sf::Texture texture;

    //object
    Ball* ball;

    //Enemies
    Enemies* enemyGirl;
    Enemies* enemyTYW;

    // function
    void initCharacter();
    void initBall();
    void initEnemies();
    void initTexture();
    void initSprite(sf:: RenderTarget* target);
    void initBackGround();

public:

    GameState(sf::RenderWindow* window, std:: stack<State*>* states);  // constructor

    virtual ~GameState();  // destructor

    // functions
    void endstate();
    void updateInput(const float& dt);
    void updatePlayer();
    void updateEnemy();
    void checkSmash(int character);
    void updateBallPlayerCollision();
    void updatePlayerEnemiesCollision(sf::RenderTarget* target);
    void updateBall(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);



};

#endif //PD110_1_FP_GAMESTATE_H
