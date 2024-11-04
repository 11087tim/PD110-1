# PD110-1

## 1. Overview

### Program Structure:
- **Game.cpp**: This file contains the game engine, structured around the initialize -> update -> render pattern, which serves as the framework for the entire game.
- **Entity.cpp**: A parent class for all game objects. Its child classes include `player.cpp`, `ball.cpp`, and `Enemies.cpp`, which represent the main player, the volleyball, and obstacles, respectively. Through inheritance, various entities share common functionalities such as `initTexture` and `initSprite`, allowing developers to quickly integrate assets. Additionally, `Entity.cpp` uses a stack-based `State*` data structure to connect different game states to the main game window.

- **State.cpp**: The parent class for managing game states. Its child classes include `mainMenuState`, `gameState`, `OptionState`, `PauseState`, and `StopState`, controlling the main menu, gameplay screen, settings menu, pause screen, and stop screen. Using inheritance, each state has access to shared methods like `update` and `render`, reducing redundant compilation.

### Additional Components:
- **Button.cpp**: Provides customizable button elements with options for size, text, and a flash effect for enhanced visual feedback.
- **ScoreBoard.cpp**: Manages the score display within `gameState.cpp`. Once a score threshold is reached, it signals to terminate the game.

## 2. System Design and Algorithms

### Game Features
- **Gravity Simulation**: To mimic real-life physics, the `Ball` class includes a private variable, `gravity`, which modifies the ball's speed through the `velocityChange()` function, creating the effect of gravity as the ball updates.
- **Smash Attack**: A `checkSmash()` function in `GameState` allows the player to perform a smash attack when jumping above a certain height, hitting the ball precisely, and pressing specific keys. Otherwise, the ball’s speed simply increases upon impact.
- **Obstacles**: Beyond standard volleyball mechanics, the `Enemy` class adds obstacles. Selecting this mode from the menu introduces barriers in the game. The `playerEnemiesCollision()` function forces the player to navigate around obstacles, enhancing the game's challenge.
