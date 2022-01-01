

#ifndef PD110_1_FP_PLAYER_H
#define PD110_1_FP_PLAYER_H

#include <iostream>
#include <SFML/Graphics.hpp>

class player {
    private:
        sf::Texture player_texture;
        sf::Sprite player_sprite;

    public:
        player() {
            //default
        }
        player(std::string ImgDirectory){
            if(!player_texture.loadFromFile(ImgDirectory)){
                std::cout << "player_picture failed.";
            }
            player_sprite.setTexture(player_texture);
        }
        void playerShow(sf::RenderWindow &window){
            window.draw(player_sprite);
        }
        void playerMove(char direction, float movingSpeed){
            if(direction == 'u'){
                player_sprite.move(0, -movingSpeed);

            }else if(direction == 'd'){
                player_sprite.move(0 , movingSpeed);
            }else if(direction == 'l'){
                player_sprite.move(-movingSpeed , 0);
            }else if(direction == 'r'){
                player_sprite.move(movingSpeed , 0);
            }
        }

};


#endif //PD110_1_FP_PLAYER_H
