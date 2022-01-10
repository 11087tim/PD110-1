#ifndef PD110_1_FP_BUTTON_H
#define PD110_1_FP_BUTTON_H

#include <iostream>
#include <ctime>
#include <cstdlib>

#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED};  // button state

class Button {
    private:

        short unsigned buttonState;

        sf::RectangleShape shape;  // shape of button
        sf::Font* font;  // button font
        sf::Text text;  // text on the button

        sf::Color idleColor;  // idle color
        sf::Color hoverColor;  // hover color
        sf::Color activeColor;  // active color

    public:
        // constructor
        Button(float x, float y, float height, float width,
           std::string text, sf::Font* font,
           sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);

        // destructor
        ~Button();

        // function
        const bool isPressed() const;
        void update(const sf::Vector2f& mousePos);  // update mousePos
        void render(sf::RenderTarget* target);  // draw the button

};


#endif //PD110_1_FP_BUTTON_H
