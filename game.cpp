//
// Created by Nina on 2021/12/30.
//
//Game初始化（window, sprite)
#include "game.h"
#include "player.h"
//#include "ball.h"
//#include "character.h"
#include <iostream>

//static const float VIEW_WIDTH = 1280.f;
//static const float VIEW_HEIGHT = 720.f;
//
//void ResizeView(const sf::RenderWindow& target, sf::View& view)
//{
//    float aspectRatioX = float(target.getSize().x/ float(target.getSize().y));
//    float aspectRatioY = float(target.getSize().y/ float(target.getSize().x));
//    view.setSize(VIEW_WIDTH * aspectRatioX, VIEW_HEIGHT * aspectRatioY);
//}
//private functions
const float windowSizeRatioYtoX = 0.5625;

void Game:: initWindow()
{
    this-> window = new sf:: RenderWindow(sf:: VideoMode(1920, 1080), "Game Test");
    this-> window->setFramerateLimit(144);
    this-> window->setVerticalSyncEnabled(false);
}

void Game:: initPlayer()
{
    this->playerJie = new Player(1, *this->window);
    this->playerCMK = new Player(2, *this->window);
}

void Game::initBall()
{
    this-> ball = new Ball();
}

//constructor/ destructor
Game::Game() {

    this-> initWindow();

    this-> initPlayer();

    this-> initBall();
}

Game:: ~Game()
{
    delete this-> window;
    delete this-> playerJie;
    delete this-> playerCMK;
    delete this-> ball;
}


//public function
void Game::run() {
    while(this-> window-> isOpen())
    {
        this-> update();
        this-> render();
    }
}

void Game::updatePlayer()
{
    //move playerJie
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->playerJie->move(-1.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->playerJie->move(1.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        this->playerJie->jump();

    this->playerJie->update(*this-> window);

    //move playerKuan
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        this->playerCMK->move(-1.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        this->playerCMK->move(1.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        this->playerCMK->jump();
    this->playerCMK->update(*this-> window);
}

void Game:: updateBallCollision()
{
//    float hitYpos = .0f; //record where the player hits ball
    if(this-> ball->getGlobalBounds().intersects(this->playerJie->getGlobalBounds()))
    {
//        hitYpos =
        if(this-> ball->getGlobalBounds().left > this->playerJie->getGlobalBounds().left + this->playerJie->getGlobalBounds().width/2)
        {
            if(this->ball-> getGlobalBounds().top + this->ball->getGlobalBounds().height < this->playerJie->getGlobalBounds().top + this->playerJie->getGlobalBounds().height/2)
                this-> ball->bounceVelocity = sf::Vector2f(5.f, -5.f);

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

//void Game:: updateGravity()
//{
//
//}

void Game:: updateBall()
{
    updateBallCollision();
    this->ball->update(*this->window);
}

void Game:: update()
{
    sf::Event e;
//    sf::View view(sf::Vector2f(.0f, .0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));
    while(this-> window-> pollEvent(e))
    {
        if(e.Event:: type == sf:: Event::Closed)
            this->window->close();
        if(e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
            this->window->close();
        //if window resized
        if(e.Event::type == sf::Event::Resized)
            this->window->setSize(sf::Vector2u (static_cast<unsigned int>(this->window->getSize().x), static_cast<unsigned int>(this->window->getSize().x * windowSizeRatioYtoX)));
//            ResizeView(*this->window, view);

    }

    updatePlayer();
    updateBall();

}

void Game::renderPlayer(sf::RenderTarget &target)
{
    this-> playerJie-> render(target);
    this-> playerCMK-> render(target);
}

void Game::renderBall(sf::RenderTarget &target)
{
    this-> ball-> render(target);
}

void Game::render() {
    this-> window-> clear();

    //draw game

    this-> renderPlayer(*this-> window);
    this-> renderBall(*this-> window);

    this-> window-> display();
}

//處理使用者輸入
//void Game::processKey() {
//    sf::Event event;
//    while (window.pollEvent(event))
//    {
//        if (event.type == sf::Event::Closed)
//            window.close();
//    }

//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//        sprite.move(-0.1, 0);
//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//        sprite.move(0.1, 0);
//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//        sprite.move(0, -0.1);
//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//        sprite.move(0, 0.1);
//}

