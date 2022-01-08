//
// Created by Nina on 2022/1/2.
//

#include "player.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include<iostream>

void Player:: initTexture(int character)
{
    //load texture
    switch(character)
    {
        case 1: //jie
            if(!this->texture.loadFromFile("/Users/nina/Desktop/C++practice/Game/texture/jie.png"))
            {
                std::cout << " ERROR: Load PLAYER image fail.";
            }
            break;
        case 2: //cmK
            if(!this->texture.loadFromFile("/Users/nina/Desktop/C++practice/Game/texture/cmKuan.png"))
            {
                std::cout << " ERROR: Load PLAYER image fail.";
            }
            break;
    }


}

void Player:: initSprite(int character, sf::RenderTarget& target)
{
    this-> sprite.setTexture(this->texture);

    //resize
    this-> sprite.scale(0.3f, 0.3f);
    if(character == 1)
        this-> sprite.setPosition(target.getSize().x*1/10, target.getSize().y - this->sprite.getGlobalBounds().height);
    else if(character == 2)
        this-> sprite.setPosition(target.getSize().x*7/10, target.getSize().y - this->sprite.getGlobalBounds().height);

}

Player:: Player(int character, sf::RenderTarget& target)
{
    this-> gravity = .3f;
    this-> movementspeed = 3.f;
    this-> jumpspeed = -5.f;

    this-> character = character;

    this-> initTexture(character);
    this-> initSprite(character, target);
}

Player:: ~Player()
{

}

//funtions
const bool Player::checkCollision() {
    return 0;
}


void Player::updateWindowBoundCollision(const sf::RenderTarget& target)
{
    if(this-> character == 1) //bounds collision for jie
    {
        //Left
        if(this->sprite.getGlobalBounds().left <= 0.f)
            this-> sprite.setPosition(0.f, this->sprite.getGlobalBounds().top);
            //Right
        else if(this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width >= target.getSize().x/2)
            this-> sprite.setPosition(target.getSize().x/2 - this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().top);
//        Top

        //Bottom
//    else if(this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height >= target.getSize().y)
//        this-> sprite.setPosition(this->sprite.getGlobalBounds().left, target.getSize().y - this->sprite.getGlobalBounds().height);
    }
    else if(this-> character == 2)//bounds collision for CMK
    {
        if(this->sprite.getGlobalBounds().left <= target.getSize().x/2)
            this-> sprite.setPosition(target.getSize().x/2, this->sprite.getGlobalBounds().top);
            //Right
        else if(this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width >= target.getSize().x)
            this-> sprite.setPosition(target.getSize().x - this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().top);
    }

    if(this->sprite.getGlobalBounds().top <= 0.f)
        this-> sprite.setPosition(this->sprite.getGlobalBounds().left, 0.f);
    
}

void Player::move(const float dirX, const float dirY)
{
    this->sprite.move(this->movementspeed * dirX, this-> movementspeed * dirY);
}

void Player:: jump()
{
    this->jumpspeed = -5.f;
    this->sprite.move(.0f, this->jumpspeed);
}



void Player:: velocityChange(const sf:: RenderTarget& target)
{
    if(this-> sprite.getPosition().y < target.getSize().y - this->sprite.getGlobalBounds().height && this->sprite.getPosition().y >= target.getSize().y *1/4)
    {
        this->sprite.move(.0f, this->jumpspeed);
        jumpspeed += gravity;
    }
    if(this->sprite.getPosition().y < target.getSize().y *1/4)
    {
        this->sprite.move(.0f, this->jumpspeed);
        jumpspeed += 2*gravity;
    }

    //initialize variables when back on the ground
    if(this-> sprite.getPosition().y == target.getSize().y - this->sprite.getGlobalBounds().height)
        this-> jumpspeed = -5.f;
}

void Player:: reset(int character, const sf::RenderTarget& target)
{
    if(character == 1)
        this-> sprite.setPosition(target.getSize().x*1/10, target.getSize().y - this->sprite.getGlobalBounds().height);
    else if(character == 2)
        this-> sprite.setPosition(target.getSize().x*7/10, target.getSize().y - this->sprite.getGlobalBounds().height);
}

void Player:: update(const sf::RenderTarget& target)
{
    this->updateWindowBoundCollision(target);
    this->velocityChange(target);
}

void Player:: render(sf::RenderTarget& target)
{
    target.draw(this-> sprite);
}


sf::FloatRect Player::getGlobalBounds()
{
    return this-> sprite.getGlobalBounds();
}

sf::Vector2f Player::getPosition()
{
    return this->sprite.getPosition();
}

float Player::getJumpspeed() {
    return this->jumpspeed;
}



