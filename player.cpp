#include "player.h"

void Player:: initTexture(int character)
{   texture = new sf::Texture;
    //load texture
    switch(character)
    {
        case 1: //jie
            if(!this->texture->loadFromFile("/Users/nina/Desktop/C++practice/Game/texture/jie.png"))
            {
                std::cout << " ERROR: Load PLAYER JIE image fail.";
            }
            break;

        case 2: //cmK
            if(!this->texture->loadFromFile("/Users/nina/Desktop/C++practice/Game/texture/cmKuan.png"))
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
    this-> sprite->scale(0.4f, 0.4f);

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
    this-> movementSpeed = 5.f;
    this-> jumpSpeed = -5.f;
    this->isjumping = false;

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

//if counter enemy, move along with enemy
void Player::counterEnemy(float enemyPosX, float enemyPosY, float enemyWidth, sf::RenderTarget* target) {

    if(this->sprite->getPosition().y + this->sprite->getGlobalBounds().height > enemyPosY)
    {
        if(this->sprite->getPosition().x + this->sprite->getGlobalBounds().width < enemyPosX + enemyWidth/2)
            this->sprite->setPosition(enemyPosX - this->sprite->getGlobalBounds().width, this->sprite->getPosition().y);
        else if(this->sprite->getPosition().x > enemyPosX + enemyWidth/2)
            this->sprite ->setPosition(enemyPosX + enemyWidth, this->sprite->getPosition().y);
//        else
//            this->sprite ->setPosition(this->sprite->getPosition().x, enemyPosY - this->sprite->getGlobalBounds().height);
    }
    else
    {
        if(this->sprite->getPosition().x < enemyPosX + enemyWidth/2)
            this->sprite->setPosition(this->sprite->getPosition().x, enemyPosY - this->sprite->getGlobalBounds().height);
        else if(this->sprite->getPosition().x > enemyPosX + enemyWidth/2)
            this->sprite ->setPosition(this->sprite->getPosition().x, enemyPosY - this->sprite->getGlobalBounds().height);
    }

    this->updateWindowBoundCollision(target);
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
//            this-> isjumping = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            this->move( -1.f, 0.f);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            this->move(1.f, 0.f);
        }
    }
    else{
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
//            this->isjumping = true;
            this->jump();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            this->move(-1.f, 0.f);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            this->move(1.f, 0.f);
        }
    }

//    if(this->sprite->getGlobalBounds().top + this->sprite->getGlobalBounds().height <= target->getSize().y)
//        this->isjumping = false;
}

void Player::render(sf::RenderTarget* target){
    target->draw(*sprite);
}


sf::Rect<float> Player::getGlobalBounds()
{
    return this-> sprite->getGlobalBounds();
}

sf::Vector2f Player::getPosition()
{
    return this->sprite->getPosition();
}

float Player::getJumpSpeed() {
    return this->jumpSpeed;
}
