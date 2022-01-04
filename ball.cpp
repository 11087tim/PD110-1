//
// Created by Nina on 2021/12/30.
//

#include "ball.h"
#include <iostream>

Ball::Ball()
{
    this-> bounceVelocity = sf:: Vector2f(5.f, -10.f);
    this-> gravity = .1f;
    this-> rotateAngle = 0.25f;
    this-> initTexture();
    this-> initSprite();
}

Ball:: ~Ball()
{

}

void Ball::initTexture()
{
    //load texture
    if(!this->texture.loadFromFile("/Users/nina/Desktop/C++practice/Game/texture/pdogs.png"))
    {
        std::cout << " ERROR: Load BALL image fail.";
    }
}

void Ball::initSprite()
{
    this-> sprite.setTexture(this->texture);

    //resize
    this-> sprite.scale(0.1f, 0.1f);
    this-> sprite.setPosition(200.f, 350.f);
}
 void Ball:: updateWindowBoundsCollision(const sf::RenderTarget& target)
{
    //Left
    if(this-> sprite.getGlobalBounds().left + this-> sprite.getGlobalBounds().width < 0.f)
    {
        this-> sprite.setPosition(0.f, this->sprite.getGlobalBounds().top);
        this-> bounceVelocity.x = 5.f;
//        this-> rotateAngle = 0.5f;
    }
    //Right
    if(this-> sprite.getGlobalBounds().left > target.getSize().x)
    {
        this-> sprite.setPosition(target.getSize().x - this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().top);
        this-> bounceVelocity.x = -5.f;
//        this-> rotateAngle = -0.5f;
    }
    //Top (Ball should fly and fall)
    if(this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height * 3 <= 0.f)
    {
        if(bounceVelocity.x > .0f)
            this-> sprite.setPosition(this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width/4, -15.f);
        else
            this-> sprite.setPosition(this->sprite.getGlobalBounds().left - this->sprite.getGlobalBounds().width/4, -15.f);
        this-> bounceVelocity.y = 5.f;
    }
    //Bottom (GameOver)!!!
    else if(this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height >= target.getSize().y)
    {
        this-> sprite.setPosition(this->sprite.getGlobalBounds().left, target.getSize().y - this->sprite.getGlobalBounds().height);
        this-> bounceVelocity = sf:: Vector2f(0.f, 0.f);
    }

    //hits the net from right side
    if(this-> sprite.getGlobalBounds().left == target.getSize().x/2 && this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height == target.getSize().y * 1/4)
    {
        this->sprite.setPosition(this->sprite.getPosition());
        this->bounceVelocity.x = 5.f;
    }
    //hits the net from the left side
    if(this-> sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width == target.getSize().x/2 && this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height == target.getSize().y * 1/4)
    {
        this->sprite.setPosition(this->sprite.getPosition());
        this->bounceVelocity.x = -5.f;
    }

}

void Ball:: velocityChange(const sf::RenderTarget& target)
{
    this-> bounceVelocity.y += this-> gravity;
}

void Ball::bounce(const sf::RenderTarget& target)
{
    this-> sprite.move(this-> bounceVelocity);
//    float bounceSpeed = this-> bounceSpeed;
//    float dy = this->sprite.getPosition().y - previousPos.y;
//    while(this->sprite.getPosition().y < )
//
//    this->sprite.move(bounceSpeed * dirX, bounceSpeed* dirY)
}

void Ball::rotate(const sf::RenderTarget &target)
{
    this->sprite.rotate(this-> rotateAngle);
}

void Ball:: update(const sf::RenderTarget& target)
{
    this->velocityChange(target);
    this->updateWindowBoundsCollision(target);
//    this->rotate(target);
    this->bounce(target);
}

void Ball:: render(sf::RenderTarget& target)
{
    target.draw(this-> sprite);
}

sf::FloatRect Ball::getGlobalBounds() {
    return this-> sprite.getGlobalBounds();
}

sf:: Vector2f Ball:: getPosition()
{

    return this->sprite.getPosition();
}
















