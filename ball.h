#ifndef PD110_1_FP_BALL_H
#define PD110_1_FP_BALL_H

#include "Entity.h"

class Ball
{
private:

    // variable
    sf::Sprite* sprite;
    sf::Texture* texture;

    // function
    void initTexture();
    void initSprite();

public:

    // public variable
    sf:: Vector2f bounceVelocity;
    float gravity;
    float rotateAngle;
    bool ballOnGround;
    float _timeElapsed;
    
    sf::Rect<float> getGlobalBounds();
    sf::Vector2f getPosition();

    Ball();
    ~Ball();

    //functions
    void updateWindowBoundsCollision(const sf::RenderTarget* target);
    void velocityChange(const sf::RenderTarget* target);
    void bounce(const sf::RenderTarget* target);
    void serve(int server);
    void rotate(const sf::RenderTarget* target);
    void update(const sf::RenderTarget* target, const float& dt);
    void render(sf::RenderTarget* target);


};


#endif //PD110_1_FP_BALL_H
