#include "ScoreBoard.h"

ScoreBoard::ScoreBoard() {
    // load font
    if (!this->font.loadFromFile("Beyond Wonderland.ttf")) {
        throw ("ERROR::GAMESTATE::COUNLD NOT LOAD FONT.");
    }
}