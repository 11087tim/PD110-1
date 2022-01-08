//
// Created by Nina on 2021/12/30.
//

#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>

class Ball
{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f serverPos;


//private functions

    void initTexture();
    void initSprite();

public:
    sf:: Vector2f bounceVelocity;
    float gravity;
    float rotateAngle;
    bool ballOnGround;
    sf::FloatRect getGlobalBounds();
    sf::Vector2f getPosition();

    Ball();
    ~Ball();

//functions
    void updateWindowBoundsCollision(const sf::RenderTarget& target);
    void velocityChange(const sf::RenderTarget& target);
    void bounce(const sf::RenderTarget& target);
    void serve(int server);
    void rotate(const sf::RenderTarget& target);
    void update(const sf::RenderTarget& target);
    void render(sf::RenderTarget& target);



};

#endif BALL_H
