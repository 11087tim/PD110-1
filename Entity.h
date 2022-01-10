#ifndef PD110_1_FP_ENTITY_H
#define PD110_1_FP_ENTITY_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stack>
#include <map>
#include<vector>

#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Entity {
protected:
    //variable
    sf::Sprite* sprite ;
    sf::Texture* texture;

    float movementSpeed;


public:
    // constructor
    Entity();

    // destructure
    virtual ~Entity();

    // functions
    void move(int character, const float& dt, const float dir_x, const float dir_y);
    void update(int character, const float& dt);
    void render(sf::RenderTarget* target);

};


#endif //PD110_1_FP_ENTITY_H
