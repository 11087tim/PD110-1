
#ifndef HELLOSFML_ENEMIES_H
#define HELLOSFML_ENEMIES_H

#include "Entity.h"

class Enemies
{
private:
    sf::Sprite* sprite ;
    sf::Texture* texture;
    int character;
    float movementspeed;
    float dir;

    void initTexture(int enemy, sf::RenderTarget* target);
    void initSprite(int enemy, sf::RenderTarget* target);

public:
    Enemies(int enemy,  sf::RenderTarget *target);
    ~Enemies();

    sf::FloatRect getGlobalBounds();
    sf::Vector2f getPosition();
    void move();
    void updateWindowBoundCollision(const sf::RenderTarget* target);
    void counterPlayer(sf::Rect<float> playerBounds);
    void reset(int enemy, sf::RenderTarget *target);
    float getMovementSpeed();
    float getDir();

    void update(sf::RenderTarget* target);
    void render(sf::RenderTarget* target);

};
#endif //HELLOSFML_ENEMIES_H
