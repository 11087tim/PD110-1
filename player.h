//
// Created by Nina on 2022/1/2.
//
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#ifndef HELLOSFML_PLAYER_H
#define HELLOSFML_PLAYER_H

class Player
{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    int character; //1 for Jie, 2 for CMK
    float gravity;
    float movementspeed;
    float directionY;
    float jumpspeed;

    //private functions
    void initTexture(int character);
    void initSprite(int character, sf::RenderTarget& target);

public:
    Player(int character, sf::RenderTarget& target);
    ~Player();

    const bool checkCollision();
    //functions
    sf:: FloatRect getGlobalBounds();
    sf::Vector2f getPosition();
    float getJumpspeed();
    void move(const float dirX, const float dirY);
    void jump();
    void velocityChange(const sf:: RenderTarget& target);
    void updateWindowBoundCollision(const sf::RenderTarget& target);
    void reset(int character, const sf::RenderTarget& target);
    void update(const sf:: RenderTarget& target);
    void render(sf::RenderTarget& target);

};
#endif //HELLOSFML_PLAYER_H
