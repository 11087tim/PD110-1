//
// Created by 張淑芬 on 2022/1/8.
//

#include "Entity.h"

Entity:: Entity()
{
    //this->shape.setSize(sf::Vector2f(50.f, 50.f));
    this->movementSpeed = 100.f;
}

Entity:: ~Entity(){

}


void Entity::move(int character, const float& dt, const float dir_x, const float dir_y) {
    if(character == 1) {
        this->sprite->move(dir_x * this->movementSpeed * dt, dir_y * this->movementSpeed * dt);
    }
    else {
        this->sprite->move(dir_x * this->movementSpeed * dt, dir_y * this->movementSpeed * dt);
    }
}
void Entity::update(int character, const float& dt){  //receive singnal
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
//    || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
        this->move(character, dt, 0.f, -1.f);
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        this->move(character, dt, -0.f, 1.f);
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        this->move(character, dt, -1.f, 0.f);
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        this->move(character, dt,  1.f, 0.f);
    }

}
void Entity::render(sf::RenderTarget* target){
    target->draw(*sprite);
}