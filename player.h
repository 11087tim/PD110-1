#ifndef PD110_1_FP_PLAYER_H
#define PD110_1_FP_PLAYER_H

# include "Entity.h"

class Player : public Entity{

    private:

        // variable
        int character; //1 for Jie, 2 for CMK
        float gravity;
        float directionY;
        float jumpSpeed;

        // function
        void initTexture(int character);
        void initSprite(int character, sf::RenderTarget* target);



    public:

        // constructor
        Player(int character, sf::RenderTarget* target);
        // destructor
        ~Player();


        //functions
        sf::FloatRect getGlobalBounds();
        sf::Vector2f getPosition();
        const bool checkCollision();
        float getJumpSpeed();
        void jump();
        void velocityChange(const sf:: RenderTarget* target);
        void updateWindowBoundCollision(const sf::RenderTarget* target);
        void reset(int character, const sf::RenderTarget* target);
        void update(const float&dt, const sf::RenderTarget* target);


};


#endif //PD110_1_FP_PLAYER_H
