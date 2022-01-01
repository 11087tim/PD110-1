#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"

int main()
{   // create gaming window
    sf::RenderWindow window(sf::VideoMode(1298, 908), "PD_final");
    // set texture & sprite of background
    sf::Texture texture_bg;
    if(!texture_bg.loadFromFile("pikachu_bg.png")){
        std::cout << "background_picture load failed." << std::endl;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture_bg);

    // set player
    player P_1("pika_p_1.jpeg");

    // main loop
    while (window.isOpen())
    {
        sf::Event event;
        // event loop
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            P_1.playerMove('u', 3.0);
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            P_1.playerMove('d', 3.0);
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            P_1.playerMove('l', 3.0);
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            P_1.playerMove('r', 3.0);
        }

        window.clear();
        window.draw(sprite);
        P_1.playerShow(window);
        window.display();
    }
}