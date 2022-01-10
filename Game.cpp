#include "Game.h"

const float windowSizeRatioYtoX = 0.5625;

// initializer
void Game::initWindow(){

    this->window = new sf::RenderWindow(sf::VideoMode(2500, 2000), "PD_final");
    this->window ->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initState(){  // push different state

    this-> states.push(new mainMenuState(this->window, &this->states));

}

// constructor
Game::Game(){

    this->initWindow();
    this->initState();
}

// destructor
Game::~Game(){

    delete this->window;
    while(!this->states.empty()){

        delete this->states.top();
        this->states.pop();
    }
}

// Functions
void Game:: updateDT(){
    /* update the dt variable with the time it takes to update and render one frame */
    this->dt = this->dtclock.restart().asSeconds();

}

void Game::updateSFLMEvents(){

    while(this->window->pollEvent(this->event)){
        if(this->event.type == sf::Event::Closed){
            this->window->close();
        }
    }


}
void Game::update(){  // collect all the event
    this-> updateDT();
    this->updateSFLMEvents();
    if(!this->states.empty()){  // state active
        this->states.top()-> update(this->dt);

        if (this->states.top()->getEnd()){
            this->states.top()->endstate();
            delete this->states.top();
            this->states.pop();
        }

    }
    // application end
    else{
        std::cout << "end the game" << std::endl;
        this->window->close();
    }

}

void Game::render(){  // respond to all the events
    this->window->clear();

    // Render object
    if(!this->states.empty()){
        this->states.top()-> render(this->window);
    }

    this->window->display();

}

void Game::run(){  // start game engine
    while(this->window->isOpen()){
        this->update();
        this->render();
    }
}
