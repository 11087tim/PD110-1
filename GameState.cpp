//
// Created by Nina on 2022/1/10.
//

#include "GameState.h"
const float hitBallVrate = 3.5f;
const float smashBallVrate = 6.f;
const sf::Vector2f hitBallVelocity = sf::Vector2f(3.f, 2.5f);
const sf::Vector2f smashBallVelocity = sf::Vector2f(15.f, .5f);

void GameState::initCharacter() {
    this->playerJie = new Player(1, this->window);
    this->playerCMK = new Player(2, this->window);

}

void GameState::initEnemies() {
    this->enemyGirl = new Enemies(1, this->window);
    this->enemyTYW = new Enemies(2, this->window);
}

void GameState::initTexture() {
    //load texture
    if(!this->texture.loadFromFile("/Users/nina/Desktop/C++practice/Game/texture/background.png"))
    {
        std::cout << " ERROR: Load BACKGROUND image fail.";
    }
}

void GameState::initSprite(sf::RenderTarget* target) {
    //resize
    sf::Vector2<unsigned int> windowsize = target->getSize();
    sf::Vector2<unsigned int> texturesize = this->texture.getSize();
    float ScaleX = (float) windowsize.x / texturesize.x;
    float ScaleY = (float) windowsize.y / texturesize.y;
    this-> sprite.scale(ScaleX, ScaleY);

    this-> sprite.setTexture(this->texture);

    this-> sprite.setPosition(0.f, 0.f);
}

void GameState::initBackGround() {
    this->initTexture();
    this->initSprite(this->window);
}

void GameState::initBall(){
    ball = new Ball();
}

GameState::GameState(sf::RenderWindow* window, std:: stack<State*>* states): State(window, states)  // constructor
{
    this-> initBackGround();
    this-> initBall();
    this->initCharacter();
    this->initEnemies();
    std::cout << "gameState is create. " << "\n";
}
GameState::~GameState(){  // destructor
    delete this-> playerJie;
    delete this-> playerCMK;
    delete this-> ball;
    delete this-> enemyGirl;
    delete this-> enemyTYW;

}

// functions

void GameState::endstate(){  // debugger
    std::cout << "end the gamestate." << std::endl;
}

void GameState::updateInput(const float &dt) {
    this->checkForEnd();
}

void GameState::updatePlayer() {
    //if ball falls on ground, reset player position
    if(this->ball->ballOnGround == true)
    {
        playerJie->reset(1, this->window);
        playerCMK->reset(2, this->window);

    }
    this->updatePlayerEnemiesCollision(this->window);

}

void GameState:: updateEnemy()
{
    if(this->ball->ballOnGround == true)
    {
        enemyGirl->reset(1, this->window);
        enemyTYW->reset(2, this->window);
    }
}

//Player and Enemies counter
void GameState::updatePlayerEnemiesCollision(sf:: RenderTarget* target) {

    if(this-> enemyGirl->getGlobalBounds().intersects(this->playerJie->getGlobalBounds()))
    {
        this->playerJie->counterEnemy(this->enemyGirl->getPosition().x, this->enemyGirl->getPosition().y, this->enemyGirl->getGlobalBounds().width, this->window);
//        this->playerJie->move(this->enemyGirl->getDir(), 0.f);
    }

    if (this->enemyTYW->getGlobalBounds().intersects(this->playerCMK->getGlobalBounds()))
    {
        this->playerCMK->counterEnemy(this->enemyTYW->getPosition().x, this->enemyTYW->getPosition().y, this->enemyTYW->getGlobalBounds().width, this->window);
//        this->playerCMK->move(this->enemyTYW->getDir(), 0.f);
    }
}

void GameState:: checkSmash(int character)
{
    switch(character)
    {
        case 1:
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                if(this->playerJie->getPosition().y < this->window->getSize().y / 2
                    && this->ball->getPosition().x > this->playerJie->getGlobalBounds().left + this->playerJie->getGlobalBounds().width / 2)
                    this->ball->bounceVelocity = smashBallVelocity;
                this->ball->bounceVelocity.y *= smashBallVrate;
            }
            break;
        case 2:
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                if(this->playerCMK->getPosition().y < this->window->getSize().y / 2
                    && this->ball->getPosition().x < this->playerCMK->getGlobalBounds().left + this->playerJie->getGlobalBounds().width / 2)
                    this->ball->bounceVelocity = sf::Vector2f(-smashBallVelocity.x, smashBallVelocity.y);
                this->ball->bounceVelocity.y *= smashBallVrate;
            }
            break;
    }

}

void GameState:: updateBallPlayerCollision()
{
    sf::Rect<float> ballGlobalBounds = this->ball->getGlobalBounds();
    sf::Rect<float> playerGlobalBounds;
    bool intersect = false;

    if(ballGlobalBounds.intersects(this->playerJie->getGlobalBounds()))
    {
        playerGlobalBounds = this->playerJie->getGlobalBounds();
        intersect = true;
        if(ballGlobalBounds.left > playerGlobalBounds.left + playerGlobalBounds.width * 0.6)
        {
            if(ballGlobalBounds.top + ballGlobalBounds.height < playerGlobalBounds.top + playerGlobalBounds.height/2)
            {
                this-> ball->bounceVelocity = sf::Vector2f(hitBallVelocity.x, - hitBallVelocity.y);
                this->checkSmash(1);
            }
            else
            {
                this-> ball->bounceVelocity = hitBallVelocity;
                this->checkSmash(1);
            }
//            this-> ball->rotateAngle = 0.5f;
        }

        else if(ballGlobalBounds.left + ballGlobalBounds.width < playerGlobalBounds.left + playerGlobalBounds.width * 0.2)
        {
            if(ballGlobalBounds.top + ballGlobalBounds.height < playerGlobalBounds.top + playerGlobalBounds.height/2)
            {
                this-> ball->bounceVelocity = -hitBallVelocity;
                this->checkSmash(1);
            }

            else
            {
                this-> ball->bounceVelocity = sf::Vector2f(-hitBallVelocity.x, hitBallVelocity.y);
                this->checkSmash(1);
            }

//            this-> ball->rotateAngle = -0.5f;
        }
        else if(ballGlobalBounds.left + ballGlobalBounds.width < playerGlobalBounds.left + playerGlobalBounds.width * 0.4
                && ballGlobalBounds.left + ballGlobalBounds.width > playerGlobalBounds.left + playerGlobalBounds.width * 0.2)
        {
            this->ball->bounceVelocity = sf::Vector2f(-hitBallVelocity.x * 0.5, -hitBallVelocity.y);
            this->checkSmash(1);
        }
        else
        {
            this->ball->bounceVelocity = sf::Vector2f(hitBallVelocity.x * 0.75, -hitBallVelocity.y);
            this->checkSmash(1);
        }


    }
    else if(ballGlobalBounds.intersects(this->playerCMK->getGlobalBounds()))
    {
        playerGlobalBounds = this->playerCMK->getGlobalBounds();
        intersect = true;
        if(ballGlobalBounds.left > playerGlobalBounds.left + playerGlobalBounds.width * 0.8)
        {
            if(ballGlobalBounds.top + ballGlobalBounds.height < playerGlobalBounds.top + playerGlobalBounds.height/2)
            {
                this-> ball->bounceVelocity = sf::Vector2f(hitBallVelocity.x, - hitBallVelocity.y);
                this->checkSmash(2);
            }


            else
            {
                this-> ball->bounceVelocity = hitBallVelocity;
                this->checkSmash(2);
            }

//            this-> ball->rotateAngle = 0.5f;
        }

        else if(ballGlobalBounds.left + ballGlobalBounds.width < playerGlobalBounds.left + playerGlobalBounds.width * 0.6)
        {
            if(ballGlobalBounds.top + ballGlobalBounds.height < playerGlobalBounds.top + playerGlobalBounds.height/2)
            {
                this-> ball->bounceVelocity = -hitBallVelocity;
                this->checkSmash(2);
            }

            else
            {
                this-> ball->bounceVelocity = sf::Vector2f(-hitBallVelocity.x, hitBallVelocity.y);
                this->checkSmash(2);
            }

//            this-> ball->rotateAngle = -0.5f;
        }
        else if(ballGlobalBounds.left + ballGlobalBounds.width < playerGlobalBounds.left + playerGlobalBounds.width * 0.6
                && ballGlobalBounds.left + ballGlobalBounds.width > playerGlobalBounds.left + playerGlobalBounds.width * 0.2)
        {
            this->ball->bounceVelocity = sf::Vector2f(-hitBallVelocity.x * 0.75, -hitBallVelocity.y);
            this->checkSmash(2);
        }
        else
        {
            this->ball->bounceVelocity = sf::Vector2f(hitBallVelocity.x * 0.5, -hitBallVelocity.y);
            this->checkSmash(2);
        }
    }

    if(intersect)
        //when hit ball bounces faster
        this-> ball-> bounceVelocity.y *= hitBallVrate;
}

void GameState::updateBall(const float& dt) {

    updateBallPlayerCollision();
    this->ball->update(this->window, dt);

}

void GameState::update(const float& dt){
    this->updateMousePosition();
    this-> updateInput(dt);
    this->ball->update(this->window, dt);
    this-> playerJie->update(dt, this-> window);
    this-> playerCMK->update(dt, this->window);
    this-> enemyGirl->update(this->window);
    this->enemyTYW->update(this->window);
    this-> updateBall(dt);
    this-> updatePlayer();
    this-> updateEnemy();

}

void GameState:: render(sf::RenderTarget* target){

    if (!target)
        target = window;

    target->draw(sprite);
    this->ball->render(this->window);
    this->playerJie->render(this->window);
    this->playerCMK->render(this->window);
    this->enemyGirl->render(this->window);
    this->enemyTYW->render(this->window);

}
