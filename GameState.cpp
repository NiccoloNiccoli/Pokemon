//
// Created by Niccolò Niccoli on 08/07/2020.
//

#include "GameState.h"
#include "Battle.h"

State GameState::state = STATE_MAP;
sf::Clock GameState::timer;
void GameState::changeState(State nextState) {
    if(nextState!=state){
        switch (nextState){
            case STATE_MAP:
                state = STATE_MAP;
                //TODO-creare degli allenatori da mettere sulla mappa, caricarli/passarli a un vettore dentro map
                //something
                break;

            case STATE_BATTLE:
                state = STATE_BATTLE;
                break;

            case STATE_POKEMON_CENTER:
                state = STATE_POKEMON_CENTER;
                //tp to pokemon center
                break;
        }
        resetTimer();
    }
}

/*
void GameState::changeState(State nextState,Trainer& player, Pokemon* wildPokemon) {
    if((nextState!=state)&&(nextState==STATE_BATTLE)){
        state=STATE_BATTLE;
        Battle* battle;
        battle = new Battle(player, *wildPokemon);
    }
}*/
/*
void GameState::draw(sf::RenderWindow window, Battle *battle, Trainer& player, Pokemon* wildPokemon) {
    battle->draw(window,player,*wildPokemon);
}
*/
State GameState::getState() {
    return state;
}

void GameState::resetTimer() {
    timer.restart();
}

float GameState::getTime() {
    return timer.getElapsedTime().asSeconds();
}
