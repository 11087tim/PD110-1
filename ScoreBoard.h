#ifndef PD110_1_FP_SCOREBOARD_H
#define PD110_1_FP_SCOREBOARD_H

#include "Entity.h"

class ScoreBoard {

    private:
        // variable
        sf::Text left_score;
        sf::Text right_score;
        sf::Font font;

        //function


    public:
        ScoreBoard();
        ~ScoreBoard();

        void update(float& dt);  // receive singal
        void render(sf::RenderTarget* target);

};


#endif //PD110_1_FP_SCOREBOARD_H
