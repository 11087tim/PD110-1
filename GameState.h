#ifndef PD110_1_FP_GAMESTATE_H
#define PD110_1_FP_GAMESTATE_H

#include "State.h"
#include "player.h"
#include "ball.h"

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

        // function
        void initCharacter();
        void initBall();
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
        void updateBallCollision();
        void updateBall();
        void update(const float& dt);
        void render(sf::RenderTarget* target = nullptr);
};

#endif //PD110_1_FP_GAMESTATE_H
