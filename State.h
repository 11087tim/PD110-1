#ifndef PD110_1_FP_STATE_H
#define PD110_1_FP_STATE_H

#include "Entity.h"


class State{
    private:


    protected:
    // variables
    std:: stack<State*>* states;  // a pointer point to stack in Game.h
    sf:: RenderWindow* window;  // window ptr
    bool wantEnd;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;  // mouse view


    // resources
    std::vector<sf::Texture> textures;

    public:

    State(sf::RenderWindow* window, std:: stack<State*>* states );  // constructor
    virtual ~State();  // destructor

    // functions
    virtual void checkForEnd();
    virtual void endstate() = 0;
    virtual void updateMousePosition();
    const bool& getEnd() const;
    virtual void updatekeybinds(const float& dt);
    virtual void update(const float& dt) =0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;

};

#endif //PD110_1_FP_STATE_H
