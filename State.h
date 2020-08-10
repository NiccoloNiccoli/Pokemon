//
// Created by Niccolò Niccoli on 10/08/2020.
//

#ifndef POKEMON_STATE_H
#define POKEMON_STATE_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "Game.h"


class State {
public:
    State(Game* gamePtr);
    virtual ~State() {};
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void changeState(State* nextState) = 0;
    virtual void update() = 0;
    virtual void handleInput(sf::Event event) = 0;
    virtual GameState getStateName();

protected:
    Game* game;
    GameState stateName;
};


#endif //POKEMON_STATE_H
