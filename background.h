//
// Created by Nina on 2022/1/8.
//
#include "player.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include<iostream>

#ifndef HELLOSFML_BACKGROUND_H
#define HELLOSFML_BACKGROUND_H
class Background
{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    void initTexture();
    void initSprite(sf:: RenderTarget& target);

public:
    Background(sf:: RenderTarget& target);
    ~Background();
    void render(sf:: RenderTarget& target);
};


#endif //HELLOSFML_BACKGROUND_H
