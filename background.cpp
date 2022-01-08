//
// Created by Nina on 2022/1/8.
//
# include "background.h"

Background::Background(sf:: RenderTarget& target)
{
    this->initTexture();
    this->initSprite(target);
}
Background:: ~Background()
{

}

void Background::initTexture()
{
    //load texture
    if(!this->texture.loadFromFile("/Users/nina/Desktop/C++practice/Game/texture/background.png"))
    {
        std::cout << " ERROR: Load BALL image fail.";
    }
}

void Background::initSprite(sf::RenderTarget& target)
{
    //resize
    sf::Vector2<unsigned int> windowsize = target.getSize();
    sf::Vector2<unsigned int> texturesize = this->texture.getSize();
    float ScaleX = (float) windowsize.x / texturesize.x;
    float ScaleY = (float) windowsize.y / texturesize.y;
    this-> sprite.scale(ScaleX, ScaleY);

    this-> sprite.setTexture(this->texture);

    this-> sprite.setPosition(0.f, 0.f);
}


void Background:: render(sf::RenderTarget& target)
{
    target.draw(this-> sprite);
}