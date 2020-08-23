//
// Created by Niccolò Niccoli on 10/08/2020.
//

#ifndef POKEMON_STATEBATTLE_H
#define POKEMON_STATEBATTLE_H


#include "State.h"

class StateBattle : public State {
public:
    explicit StateBattle(Game *gamePtr);
    void draw(sf::RenderWindow& window) override;
    void changeState(State* nextState) override;
    void update() override;
    void handleInput(sf::Event event, sf::RenderWindow &window) override;
    GameState getStateName() override;

};


#endif //POKEMON_STATEBATTLE_H
