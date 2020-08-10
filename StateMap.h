//
// Created by Niccolò Niccoli on 10/08/2020.
//

#ifndef POKEMON_STATEMAP_H
#define POKEMON_STATEMAP_H


#include "State.h"

class StateMap : public State {
public:
    explicit StateMap(Game *gamePtr);
    void draw(sf::RenderWindow& window) override;
    void changeState(State* nextState) override;
    void update() override;
    void handleInput(sf::Event event) override;
};


#endif //POKEMON_STATEMAP_H
