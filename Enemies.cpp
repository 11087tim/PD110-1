#include "Enemies.h"

void Enemies::initTexture(int enemy, sf::RenderTarget* target) {

    this->texture = new sf::Texture;
    switch(enemy) {

        case 1: //ACgirl
            if (!this->texture->loadFromFile("/Users/nina/Desktop/C++practice/Game/texture/ACgirl.png")) {
                std::cout << " ERROR: Load ENEMY ACgirl image fail.";
            }

            break;

        case 2: //TYW
            if (!this->texture->loadFromFile("/Users/nina/Desktop/C++practice/Game/texture/ywTsai.png")) {
                std::cout << " ERROR: Load ENEMY TYW image fail.";
            }
            break;

    }
}


void Enemies::initSprite(int enemy, sf::RenderTarget* target) {
    sprite = new sf::Sprite;
    this->sprite->setTexture(*texture);

    // set enemy position
    if (enemy == 1) {
        this->sprite->setPosition(0.f, target->getSize().y - this->sprite->getGlobalBounds().height);
        this->sprite->scale(.5f, .5f);
    } else {
        this->sprite->setPosition(target->getSize().x - this->sprite->getGlobalBounds().width,
                                  target->getSize().y - this->sprite->getGlobalBounds().height);
        this->sprite->scale(0.12f, 0.12f);

    }
}
Enemies:: Enemies(int enemy, sf::RenderTarget *target)
{
    this->initTexture(enemy, target);
    this->initSprite(enemy, target);

    movementspeed = 2.5f;
    switch(enemy)
    {
        case 1:
            dir = 1.f;
            character = 1;
            break;
        case 2:
            dir = -1.f;
            character = 2;
            break;
    }
}

Enemies:: ~Enemies()
{

}

void Enemies::updateWindowBoundCollision(const sf::RenderTarget *target) {

    if(this->character == 1) {

        if (this->sprite->getGlobalBounds().left <= 0.f) {
            this->dir = 1.f;
            this->sprite->setPosition(0.f, target->getSize().y - this->sprite->getGlobalBounds().height);
        }
        else if (this->sprite->getGlobalBounds().left + this->sprite->getGlobalBounds().width >=
                   target->getSize().x / 2) {
            this->dir = -1.f;
            this->sprite->setPosition(target->getSize().x / 2 - this->sprite->getGlobalBounds().width,
                                      target->getSize().y - this->sprite->getGlobalBounds().height);
        }
    }

    if(this->character == 2){

        if(this-> sprite-> getGlobalBounds().left <= target->getSize().x/2)
        {
            this-> dir = 1.f;
            this-> sprite->setPosition(target->getSize().x/2, target->getSize().y - this->sprite->getGlobalBounds().height);
        }

        else if(this-> sprite -> getGlobalBounds().left + this-> sprite->getGlobalBounds().width >= target->getSize().x)
        {
            this-> dir = -1.f;
            this-> sprite->setPosition(target->getSize().x - this->sprite->getGlobalBounds().width, target->getSize().y - this->sprite->getGlobalBounds().height);
        }
    }
}

void Enemies::move() {
    this-> sprite -> move(this-> movementspeed * this->dir, 0.f);
}

void Enemies::reset(int enemy, sf::RenderTarget* target)
{
    switch(enemy)
    {
        case 1:
            this->sprite->setPosition(0.f, target->getSize().y - this->sprite->getGlobalBounds().height);
            break;
        case 2:
            this->sprite->setPosition(target->getSize().x - this->sprite->getGlobalBounds().width,
                                      target->getSize().y - this->sprite->getGlobalBounds().height);
            break;
    }
}

sf::FloatRect Enemies::getGlobalBounds() {
    return this-> sprite->getGlobalBounds();
}

sf::Vector2f Enemies::getPosition() {
    return this->sprite->getPosition();
}

float Enemies::getMovementSpeed() {
    return this->movementspeed;
}

float Enemies::getDir() {
    return this->dir;
}


void Enemies::update(sf::RenderTarget* target) {
    this->updateWindowBoundCollision(target);
    this->move();
}

void Enemies::render(sf::RenderTarget* target) {
    target-> draw(*sprite);
}

//void Enemies::counterPlayer(sf::Rect<float> playerBounds) {
//    sf::Rect<float> enemyBounds = this->sprite->getGlobalBounds();
//    sf:: Vector2f enemyPos = this->sprite->getPosition();
//    if(enemyPos.x
//}








