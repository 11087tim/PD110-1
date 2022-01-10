#include "State.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states){  // constructor
    this->window = window;
    this->states = states;  // pointer of stack states
    this->wantEnd = false;

}

State::~State(){  // destructor

}


// functions
void State::checkForEnd(){  // press ESC to end
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        this->wantEnd = true;

}

const bool & State::getEnd() const {  // return boolean of wantEnd
    return this->wantEnd;
}

void State::updatekeybinds(const float &dt) {

}

void State::updateMousePosition(){
    this-> mousePosScreen = sf::Mouse::getPosition();
    this-> mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->  mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
    //std:: cout << " update mouse !" << std::endl;
}


void State::update(const float& dt){
    this->updateMousePosition();
}

void State::render(sf::RenderTarget* target){

};


