#include "Button.h"

Button:: Button(float x, float y, float height, float width, std::string text, sf::Font* font,
                sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor){

    this->buttonState = BTN_IDLE;
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::Yellow);
    this->text.setCharacterSize(30);
    this->text.setPosition(
            this->shape.getPosition().x +(this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
            this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
            );
    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    this->shape.setFillColor(this->idleColor);
}

Button::~Button(){

}

// accessor
const bool Button::isPressed() const{
    if (this->buttonState == BTN_PRESSED){  // button is pressed
        return true;
    }
    return false;

}

void Button:: update(const sf::Vector2f& mousePos){
    // update the boolean for hover and pressed

    // idle
    this->buttonState = BTN_IDLE;

    // Hover
    if(this->shape.getGlobalBounds().contains(mousePos)){
        this->buttonState = BTN_HOVER;
        // pressed
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            this->buttonState = BTN_PRESSED;
        }
    }

    switch(this->buttonState){
        case BTN_IDLE:
            this->shape.setFillColor(this->idleColor);
            break;
        case BTN_HOVER:
            this->shape.setFillColor(this->hoverColor);
            break;
        case BTN_PRESSED:
            this->shape.setFillColor(this->activeColor);
            break;

        default:
            this->shape.setFillColor(sf::Color::Red);
            break;
    }
}

void Button:: render(sf::RenderTarget* target){
    target->draw(this->shape);
    target->draw(this->text);
}





