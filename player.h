#ifndef PD110_1_FP_PLAYER_H
#define PD110_1_FP_PLAYER_H

# include "Entity.h"

class Player {
private:
    // picture resource
    sf::Sprite* sprite ;
    sf::Texture* texture;

    // variable
    int character; //1 for Jie, 2 for CMK
    float gravity = .3f;
    float movementSpeed = 5.f;
    float jumpSpeed = -5.f;
    bool isjumping = false;

    // function
    void initTexture(int character);
    void initSprite(int character, sf::RenderTarget* target);

public:
    // constructor
    Player(int character, sf::RenderTarget* target);
    // destructor
    ~Player();

    //functions
    sf::Rect<float> getGlobalBounds();
    sf::Vector2f getPosition();
    const bool checkCollision();
    float getJumpSpeed();
    void jump();
    void move(const float dir_x, const float dir_y);
    void velocityChange(const sf:: RenderTarget* target);
    void updateWindowBoundCollision(const sf::RenderTarget* target);
    void counterEnemy(float enemyPosX, float enemyPosY, float enemyWidth, sf::RenderTarget* target);
    void reset(int character, const sf::RenderTarget* target);
    void update(const float&dt, const sf::RenderTarget* target);
    void render(sf::RenderTarget* taget);
};


#endif //PD110_1_FP_PLAYER_H
