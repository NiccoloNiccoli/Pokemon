//
// Created by Niccolò Niccoli on 08/07/2020.
//

#ifndef POKEMON_GAMESTATE_H
#define POKEMON_GAMESTATE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "Pokemon.h"
#include "Trainer.h"
#include "Battle.h"

enum State{
    STATE_MAP,
    STATE_BATTLE,
    STATE_POKEMON_CENTER
};
class GameState {
public:
    static void changeState(State nextState);
    static void changeState(State nextState, Trainer& player, Pokemon* wildPokemon);
    void draw(sf::RenderWindow window, Battle* battle,Trainer& player, Pokemon* wildPokemon);
    static State getState();
    static float getTime();
    static void resetTimer();

private:
    static State state;
    static sf::Clock timer;


};


#endif //POKEMON_GAMESTATE_H
