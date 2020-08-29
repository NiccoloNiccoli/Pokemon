//
// Created by Niccolò Niccoli on 10/08/2020.
//

#ifndef POKEMON_STATE_H
#define POKEMON_STATE_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "Game.h"


class State {
public:
    virtual ~State() = default;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void changeState(State* nextState) = 0;
    virtual void update() = 0;
    virtual void handleInput(sf::Event event, sf::RenderWindow &window) = 0;
    virtual GameState getStateName() = 0;

    GameState stateName;
protected:
    Game* game;
};


#endif //POKEMON_STATE_H
