//
// Created by Niccolò Niccoli on 10/08/2020.
//

#include <fstream>
#include <iostream>
#include <stdio.h>
#include "Game.h"
#include "StateMap.h"
#include "StatePokemonCenter.h"
#include "StateBattle.h"
#include "StateMainMenu.h"
#include "debug.h"

sf::Clock Game::timer;
Game* Game::instance = nullptr;

Game::Game() {
    currentState = new StateMainMenu(this);
    remove("../Saves/tmp.txt");//remove tmp file from previous session
}



void Game::changeState(GameState nextGameState) {
    State* nextState = createPointer(nextGameState);
    currentState->changeState(nextState);
    timer.restart();
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

void Game::save() {
    //provo ad aprire il file dei salvataggi
    //se non esiste lo creo
    //ci scrivo nome, team, dove mi trovo e da quanto tempo sto giocando
    std::ofstream saveFile("../Saves/saves.txt", std::ios::trunc);
    if(saveFile.is_open()){
        saveFile << player.getName()<<" ";
        saveFile << player.getXPosition() << " " << player.getYPosition()<<" ";
        saveFile << player.getMoney()<<" ";
        saveFile << player.team.size()<<" ";
        for (auto i : player.team){
            saveFile << i->getName() << " " << i->getCurrentHp() << " " <<  i->getLevel()<<" ";
            for (int j = 0; j < 4; j++)
                saveFile << i->moves[j].getNUsage() << " ";
        }
        saveFile << map.getName()<<" ";
        saveFile << previousSessionsPlayTime + playTime.getElapsedTime().asSeconds();
#ifdef DEBUG
    std::cout<<"Saved!"<<std::endl;
#endif
    }
    std::string tmpNpcFile("../Saves/tmp.txt");
    std::ifstream tmpNpcList(tmpNpcFile);

    if(tmpNpcList.is_open()){
        std::string mapName;
        int id;
        std::multimap<std::string, int> table;
        while(tmpNpcList >> mapName >> id){
            table.emplace(mapName,id);
        }
        for (auto i : table) {
            std::string oldNpcFile("../Maps/" + i.first + "/npclist.txt");
            std::ifstream oldNpcList(oldNpcFile);
            std::string newNpcFile("../Maps/" + i.first + "/tmpnpclist.txt");
            std::ofstream newNpcList(newNpcFile);
            if (oldNpcList.is_open()) {
                int _id, _x, _y;
                std::string _state;
                while (oldNpcList >> _id >> _x >> _y >> _state) {
                    for (auto j : table) {
                        if (_id == i.second)
                            _state = "false";
                    }
                    newNpcList << _id << " " << _x << " " << _y << " " << _state << "\n";
                }
            }
            oldNpcList.close();
            newNpcList.close();
            tmpNpcList.close();
            remove(oldNpcFile.c_str());
            rename(newNpcFile.c_str(), oldNpcFile.c_str());
            remove(tmpNpcFile.c_str());
        }

    }


}

bool Game::doesSaveFileExists() {
    return std::ifstream("../Saves/saves.txt").good();
}

float Game::getPreviousSessionsPlayTime() const {
    return previousSessionsPlayTime;
}

void Game::load() {

    if(doesSaveFileExists()) {
        std::ifstream saveFile("../Saves/saves.txt");
        if (saveFile.is_open()) {
            std::string playersName, pokemonsName, mapName;
            int money, teamSize, hpCurrent, lvl, xpos, ypos, usesLeft;
            float playtime;
            saveFile >> playersName >> xpos >> ypos >> money >> teamSize;
            player.setName(playersName);
            player.setPosition(xpos, ypos);
            player.setMoney(money);
            player.team.clear();
            Pokemon **playersPokemon;
            playersPokemon = new Pokemon *[teamSize];
            for (int i = 0; i < teamSize; i++) {
                saveFile >> pokemonsName >> hpCurrent >> lvl;
                playersPokemon[i] = new Pokemon(pokemonsName, lvl);
                playersPokemon[i]->loseHp(playersPokemon[i]->getMaxHp() - hpCurrent);
                player.team.emplace_back(playersPokemon[i]);
                for(int j = 0; j <4; j++){
                    saveFile >> usesLeft;
                    player.team[i]->moves[j].setNUsage(usesLeft);
                }
            }
            saveFile >> mapName >> playtime;
            previousSessionsPlayTime = playtime;
            //      map =  Map("tileset1_1.png", 27, 15, mapName); FIXME, per ora non fa nulla ma se faccio il centro pokemon si
        }
    }
}

