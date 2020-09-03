//
// Created by Niccolò Niccoli on 23/08/2020.
//

#ifndef POKEMON_STATEPAUSEMENU_H
#define POKEMON_STATEPAUSEMENU_H


#include "State.h"

class StatePauseMenu: public State {
public:
    explicit StatePauseMenu(Game *gamePtr);
    void draw(sf::RenderWindow& window) override;
    void changeState(State* nextState) override;
    void update() override;
    void handleInput(sf::Event event, sf::RenderWindow &window) override;
    GameState getStateName() override;
    void setPreviousState(State* state);
    void playMusic() override ;

private:
    State* previousState;
    int selectedButton = 0;
   sf::Text buttons [3];
   sf::Font font;
};



#endif //POKEMON_STATEPAUSEMENU_H
