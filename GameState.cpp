#include "GameState.h"

void GameState::initCharacter() {
    this->playerJie = new Player(1, this->window);
    this->playerCMK = new Player(2, this->window);

}

void GameState::initTexture() {
    //load texture
    if(!this->texture.loadFromFile("background.png"))
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

        std::cout << "gameState is create. " << "\n";
}
GameState::~GameState(){  // destructor
    delete this-> playerJie;
    delete this-> playerCMK;
    delete this-> ball;

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

}

void GameState:: updateBallCollision()
{
//    float hitYpos = .0f; //record where the player hits ball
    if(this-> ball->getGlobalBounds().intersects(this->playerJie->getGlobalBounds()))
    {
//        hitYpos =
        if(this-> ball->getGlobalBounds().left > this->playerJie->getGlobalBounds().left + this->playerJie->getGlobalBounds().width/2)
        {
            if(this->ball-> getGlobalBounds().top + this->ball->getGlobalBounds().height < this->playerJie->getGlobalBounds().top + this->playerJie->getGlobalBounds().height/2)
                this-> ball->bounceVelocity += sf::Vector2f(1.f, this->playerJie->getJumpSpeed());

            else
                this-> ball->bounceVelocity = sf::Vector2f(5.f, 5.f);
//            this-> ball->rotateAngle = 0.5f;
        }

        else
        {
            if(this->ball-> getGlobalBounds().top + this->ball->getGlobalBounds().height < this->playerJie->getGlobalBounds().top + this->playerJie->getGlobalBounds().height/2)
                this-> ball->bounceVelocity = sf::Vector2f(-5.f, -5.f);
            else
                this-> ball->bounceVelocity = sf::Vector2f(-5.f, 5.f);
//            this-> ball->rotateAngle = -0.5f;
        }

        //when hit ball bounces faster
        this-> ball-> bounceVelocity.y *= 2.5;
        //change gravity according to position where player hits ball
        if(this->ball->getPosition().y - this->playerJie->getPosition().y > 50.f)
            this-> ball-> bounceVelocity.y += this-> ball-> gravity * 1.2;
    }

    if(this-> ball->getGlobalBounds().intersects(this->playerCMK->getGlobalBounds()))
    {
        if(this-> ball->getGlobalBounds().left > this->playerCMK->getGlobalBounds().left + this->playerCMK->getGlobalBounds().width/2)
        {
            if(this->ball-> getGlobalBounds().top + this->ball->getGlobalBounds().height < this->playerCMK->getGlobalBounds().top + this->playerCMK->getGlobalBounds().height/2)
                this-> ball->bounceVelocity = sf::Vector2f(5.f, -5.f);
            else
                this-> ball->bounceVelocity = sf::Vector2f(5.f, 5.f);
//            this-> ball->rotateAngle = 0.5f;
        }

        else
        {
            if(this->ball-> getGlobalBounds().top + this->ball->getGlobalBounds().height < this->playerCMK->getGlobalBounds().top + this->playerCMK->getGlobalBounds().height/2)
                this-> ball->bounceVelocity = sf::Vector2f(-5.f, -5.f);
            else
                this-> ball->bounceVelocity = sf::Vector2f(-5.f, 5.f);
//            this-> ball->rotateAngle = 0.5f;
        }

        //when hit ball bounces faster
        this-> ball-> bounceVelocity.y *= 2.5;
        //change gravity according to position where player hits ball
        if(this->ball->getPosition().y - this->playerCMK->getPosition().y > 50.f)
            this-> ball-> bounceVelocity.y += this-> ball-> gravity * 1.2;
    }
}

void GameState::updateBall() {

    updateBallCollision();
    this->ball->update(this->window);

}

void GameState::update(const float& dt){
    this->updateMousePosition();
    this-> updateInput(dt);
    this->ball->update(this->window);
    this-> playerJie->update(dt, this-> window);
    this-> playerCMK->update(dt, this->window);
    this-> updateBall();
    this-> updatePlayer();

}

void GameState:: render(sf::RenderTarget* target){

    if (!target)
        target = window;

    target->draw(sprite);
    this->ball->render(this->window);
    this->playerJie->render(this->window);
    this->playerCMK->render(this->window);

}