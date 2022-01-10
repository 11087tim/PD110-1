#include "player.h"

void Player:: initTexture(int character)
{   texture = new sf::Texture;
    //load texture
    switch(character)
    {
        case 1: //jie
            if(!this->texture->loadFromFile("Jie.png"))
            {
                std::cout << " ERROR: Load PLAYER JIE image fail.";
            }
            break;

        case 2: //cmK
            if(!this->texture->loadFromFile("cmKuan.png"))
            {
                std::cout << " ERROR: Load PLAYER KUAN image fail.";
            }
            break;
    }


}

void Player:: initSprite(int character, sf::RenderTarget* target)
{
    sprite = new sf:: Sprite;
    this-> sprite->setTexture(*texture);

    //resize
    this-> sprite->scale(0.3f, 0.3f);

    // set player position
    if(character == 1)
        this-> sprite->setPosition(target->getSize().x*1/10, target->getSize().y - this->sprite->getGlobalBounds().height);
    else if(character == 2)
        this-> sprite->setPosition(target->getSize().x*7/10, target->getSize().y - this->sprite->getGlobalBounds().height);

}

// constructor
Player:: Player(int character, sf::RenderTarget* target)
{
    this-> gravity = .3f;
    this-> movementSpeed = 3.f;
    this-> jumpSpeed = -5.f;

    this-> character = character;

    this-> initTexture(character);
    std::cout << "inittexture good" << "\n";
    this-> initSprite(character, target);
    std::cout << "initSprite good" << "\n";
}

// destructor
Player:: ~Player()
{

}

// functions

const bool Player::checkCollision() {
    return 0;
}

// update Collision
void Player::updateWindowBoundCollision(const sf::RenderTarget* target)
{
    if(this-> character == 1) //bounds collision for jie
    {
        //Left
        if(this->sprite->getGlobalBounds().left <= 0.f)
            this-> sprite->setPosition(0.f, this->sprite->getGlobalBounds().top);

        //Right
        else if(this->sprite->getGlobalBounds().left + this->sprite->getGlobalBounds().width >= target->getSize().x/2)
            this-> sprite->setPosition(target->getSize().x/2 - this->sprite->getGlobalBounds().width, this->sprite->getGlobalBounds().top);
//        Top

        //Bottom
//    else if(this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height >= target.getSize().y)
//        this-> sprite.setPosition(this->sprite.getGlobalBounds().left, target.getSize().y - this->sprite.getGlobalBounds().height);
    }
    else if(this-> character == 2)//bounds collision for CMK
    {
        if(this->sprite->getGlobalBounds().left <= target->getSize().x/2)
            this-> sprite->setPosition(target->getSize().x/2, this->sprite->getGlobalBounds().top);
            //Right
        else if(this->sprite->getGlobalBounds().left + this->sprite->getGlobalBounds().width >= target->getSize().x)
            this-> sprite->setPosition(target->getSize().x - this->sprite->getGlobalBounds().width, this->sprite->getGlobalBounds().top);
    }

    if(this->sprite->getGlobalBounds().top <= 0.f)
        this-> sprite->setPosition(this->sprite->getGlobalBounds().left, 0.f);

}



float Player::getJumpSpeed() {
    return this->jumpSpeed;
}

void Player:: velocityChange(const sf:: RenderTarget* target)
{
    if(this-> sprite->getPosition().y < target->getSize().y - this->sprite->getGlobalBounds().height && this->sprite->getPosition().y >= target->getSize().y *1/4)
    {
        this->sprite->move(.0f, this->jumpSpeed);
        this-> jumpSpeed += gravity;
    }
    if(this->sprite->getPosition().y < target->getSize().y *1/4)
    {
        this->sprite->move(.0f, this->jumpSpeed);
        this-> jumpSpeed += 2*gravity;
    }

    //initialize variables when back on the ground
    if(this-> sprite->getPosition().y == target->getSize().y - this->sprite->getGlobalBounds().height)
        this-> jumpSpeed = -5.f;
}

void Player:: reset(int character, const sf::RenderTarget* target)
{
    if(character == 1)
        this-> sprite->setPosition(target->getSize().x*1/10, target->getSize().y - this->sprite->getGlobalBounds().height);
    else if(character == 2)
        this-> sprite->setPosition(target->getSize().x*7/10, target->getSize().y - this->sprite->getGlobalBounds().height);

}

void Player:: jump(){
    this->jumpSpeed = -5.f;
    this->sprite->move(.0f, this->jumpSpeed);
}

void Player:: move(const float dir_x, const float dir_y){
    this->sprite->move(dir_x * this->movementSpeed , dir_y * this->movementSpeed );
}

void Player:: update(const float& dt, const sf::RenderTarget* target)
{
    this->updateWindowBoundCollision(target);
    this->velocityChange(target);
    // control movement
    if(character == 1) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            this->jump();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            this->move( -1.f, 0.f);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            this->move( 1.f, 0.f);
        }
    }
    else{
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            this->jump();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            this->move(-1.f, 0.f);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            this->move(1.f, 0.f);
        }

    }
}


sf::FloatRect Player::getGlobalBounds()
{
    return this-> sprite->getGlobalBounds();
}

sf::Vector2f Player::getPosition()
{
    return this->sprite->getPosition();
}

void Player::render(sf::RenderTarget* target){
    target->draw(*sprite);
}


