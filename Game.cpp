//
// Created by Niccolò Niccoli on 10/08/2020.
//

#include "Game.h"
#include "StateMap.h"
#include "StatePokemonCenter.h"
#include "StateBattle.h"

sf::Clock Game::timer;
Game* Game::instance = nullptr;

Game::Game() {
    currentState = new StateMap(this);

}



void Game::changeState(GameState nextGameState) {
    State* nextState = createPointer(nextGameState);
    currentState->changeState(nextState);
}

void Game::drawCurrentScene(sf::RenderWindow &window) {
    currentState->draw(window);
}

void Game::update() {
    currentState->update();
}

void Game::handleInput(sf::Event event) {
    currentState->handleInput(event);

}

State *Game::getCurrentState() const {
    return currentState;
}

void Game::setCurrentState(State *currentState) {
    Game::currentState = currentState;
}

bool Game::checkState(GameState state) {
   return currentState->getStateName() == state;
}

State* Game::createPointer(GameState state) {
    if(state == GameState::STATE_MAP){
        return new StateMap(this);
    }

    else if (state == GameState::STATE_BATTLE)
        return new StateBattle(this);
    else if (state == GameState::STATE_POKEMON_CENTER)
        return new StatePokemonCenter(this);
}

float Game::getTime() {
    return timer.getElapsedTime().asSeconds();
}

void Game::resetTimer() {
    timer.restart();
}

Game *Game::getInstance() {
    if (instance == nullptr)
        instance = new Game();
    return instance;
}

