#ifndef PD110_1_FP_MAINMENUSTATE_H
#define PD110_1_FP_MAINMENUSTATE_H

#include "GameState.h"
#include "Button.h"

class mainMenuState: public State{

private:

    // variable
    sf::RectangleShape background;
    sf::RectangleShape Banner;
    sf::Font font;
    sf::Text banner_text;  // text on the Banner

    // Decoration
    sf::Texture decoration_t1;
    sf::Sprite decoration_s1;
    sf::Texture decoration_t2;
    sf::Sprite decoration_s2;

    // music
    sf::Music music;

    std::map<std::string ,Button*> button;  // map the button by string

    // function
    void initFont();  // font
    void initButton();
    void initBanner();
    void initDecoration();
    void initMusic();


public:

    mainMenuState(sf::RenderWindow* window, std:: stack<State*>* states);  // constructor
    virtual ~mainMenuState();  // destructor

    // functions
    void endstate();
    void updateInput(const float& dt);
    void updateButton();
    void renderButtons(sf::RenderTarget* target = NULL);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};


#endif //PD110_1_FP_MAINMENUSTATE_H
