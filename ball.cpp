#include "ball.h"

const sf::Vector2f orgVelocity = sf::Vector2f(1.f, 2.f);

void Ball::initTexture(){
    texture = new sf::Texture;
    if(!this->texture->loadFromFile("/Users/nina/Desktop/C++practice/Game/texture/pdogs.png"))
    {
        std::cout << " ERROR: Load BALL image fail.";
    }

}

void Ball::initSprite()
{   sprite = new sf::Sprite;
    this-> sprite->setTexture(*texture);

    //resize
    this-> sprite->scale(0.1f, 0.1f);
    this-> sprite->setPosition(200.f, -10.f);
}

Ball::Ball()
{
    this-> bounceVelocity = orgVelocity;
    this-> gravity = .05f;
    this-> ballOnGround = false;
    this->_timeElapsed = 0;
    this-> initTexture();
    this-> initSprite();
}

Ball:: ~Ball()
{

}


void Ball:: updateWindowBoundsCollision(const sf::RenderTarget* target)
{
    //Left
    if(this-> sprite->getGlobalBounds().left < 0.f)
    {
        this-> sprite->setPosition(0.f, this->sprite->getPosition().y);
        this-> bounceVelocity.x = 1.f;
//        this-> rotateAngle = 0.5f;
    }
    //Right
    if(this-> sprite->getGlobalBounds().left + this->sprite->getGlobalBounds().width > target->getSize().x)
    {
        this-> sprite->setPosition(target->getSize().x - this->sprite->getGlobalBounds().width, this->sprite->getPosition().y);
        this-> bounceVelocity.x = -1.f;
//        this-> rotateAngle = -0.5f;
    }
    //Top (Ball should fly and fall)
    if(this->sprite->getGlobalBounds().top + this->sprite->getGlobalBounds().height * 2 <= 0.f)
    {
        if(bounceVelocity.x > .0f)
            this-> sprite->setPosition(this->sprite->getPosition().x + this->sprite->getGlobalBounds().width/4, -2.f);
        else
            this-> sprite->setPosition(this->sprite->getPosition().x - this->sprite->getGlobalBounds().width/4, -2.f);
        this-> bounceVelocity.y = 1.f;
    }
//        Bottom (GameOver)!!!
    else if(this->sprite->getGlobalBounds().top + this->sprite->getGlobalBounds().height >= target->getSize().y)
    {
        this-> sprite->setPosition(this->sprite->getPosition().x, target->getSize().y - this->sprite->getGlobalBounds().height);
        this-> bounceVelocity = sf:: Vector2f(0.f, 0.f);
        this-> ballOnGround = true;
    }

    //hits the net from right side
    if(this-> sprite->getGlobalBounds().left <= target->getSize().x/2 && this->sprite->getGlobalBounds().top + this->sprite->getGlobalBounds().height >= target->getSize().y * 1/2)
    {
        if(this->sprite->getPosition().x > target->getSize().x/2)
        {
            this->sprite->setPosition(target->getSize().x/2, this->sprite->getPosition().y);
            this->bounceVelocity.x = 1.f;
        }
    }
    //hits the net from the left side
    if(this-> sprite->getGlobalBounds().left + this->sprite->getGlobalBounds().width > target->getSize().x/2 && this->sprite->getGlobalBounds().top + this->sprite->getGlobalBounds().height >= target->getSize().y * 1/2)
    {
        if(this->sprite->getPosition().x < target->getSize().x/2) {
            this->sprite->setPosition(target->getSize().x/2 - this->sprite->getGlobalBounds().width, this->sprite->getPosition().y);
            this->bounceVelocity.x = -1.f;
        }
    }

}

void Ball:: velocityChange(const sf::RenderTarget* target)
{
    this-> bounceVelocity.y += this-> gravity;
}

void Ball::bounce(const sf::RenderTarget* target)
{
    this-> sprite->move(this-> bounceVelocity);
}

void Ball::serve(int server)
{
    //set ball to the server
    if(server == 1) //server is Jie
        this-> sprite->setPosition(192.f, 0.f);
    else
        this-> sprite->setPosition(1550.f, 0.f);
    this-> bounceVelocity = sf::Vector2f(orgVelocity.x, orgVelocity.y * 0.5);
}

void Ball::rotate(const sf::RenderTarget* target)
{
    this->sprite->rotate(this-> rotateAngle);
}

void Ball:: update(const sf::RenderTarget* target, const float& dt)
{
//    delay reset after ballOnGround
//    if(ballOnGround)return;
//
//    _timeElapsed += dt;
//    if(_timeElapsed < 3)return;

//    this-> serve();
    if(this-> ballOnGround == true)
    {
//        this->bounceVelocity = orgVelocity;
        if(this-> sprite->getPosition().x < target->getSize().x / 2)
            this->serve(2);
        else
            this->serve(1);
        this->ballOnGround = false;
    }

    this->velocityChange(target);
    this->updateWindowBoundsCollision(target);
//    this->rotate(target);
    this->bounce(target);
}


sf::Rect<float> Ball::getGlobalBounds() {
    return this-> sprite->getGlobalBounds();
}

sf:: Vector2f Ball:: getPosition()
{

    return this->sprite->getPosition();
}
void Ball::render(sf::RenderTarget* target){
    target->draw(*sprite);
}
