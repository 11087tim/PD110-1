#ifndef PD110_1_FP_GAME_H
#define PD110_1_FP_GAME_H

#include "mainMenuState.h"

class Game{
    private:

        // variables
        sf::RenderWindow* window;
        sf::Event event;

        sf::Clock dtclock;
        float dt = 0;
        std:: stack<State*> states;


        // initialize
        void initWindow();
        void initState();


    public:
        Game();
            // default

        virtual ~Game();

        // Functions
        void updateDT();
        void updateSFLMEvents();
        void update();
        void render();
        void run();
};



#endif //PD110_1_FP_GAME_H
