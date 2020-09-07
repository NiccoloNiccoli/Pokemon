//
// Created by Niccolò Niccoli on 10/08/2020.
//

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include "Game.h"
#include "StateMap.h"
#include "StatePokemonCenter.h"
#include "StateBattle.h"
#include "StateMainMenu.h"


sf::Clock Game::timer;
Game* Game::instance = nullptr;

Game::Game() {
    battle = new Battle();
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

void Game::handleInput(sf::Event event, sf::RenderWindow &window) {
    currentState->handleInput(event, window);

}

State *Game::getCurrentState() const {
    return currentState;
}

void Game::setCurrentState(State *_currentState) {
    Game::currentState = _currentState;
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
    else
        return nullptr;
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
        saveFile << player.getName()<<",";
        saveFile << player.getPosition().x << "," << player.getPosition().y<<",";
        saveFile << player.getMoney()<<",";
        saveFile << player.team.size()<<",";
        for (auto i : player.team){
            saveFile << i->getName() << "," << i->getCurrentHp() << "," <<  i->getLevel()<<"," << i->getExpToNextLevel()<<",";
            for (int j = 0; j < 4; j++)
                saveFile << i->getMoves(j)->getNUsage() << ",";
        }
        saveFile << map.getName()<<",";
        saveFile << previousSessionsPlayTime + playTime.getElapsedTime().asSeconds();
    }
    std::string tmpNpcFile("../Saves/tmp.txt");
    std::ifstream tmpNpcList(tmpNpcFile);

    if(tmpNpcList.is_open()){
        std::multimap<std::string, int> table;
        std::string line, mapName, id;
        while(std::getline(tmpNpcList,line)){
            std::stringstream ss(line);
            std::getline(ss, mapName, ',');
            std::getline(ss, id, ',');
            table.emplace(mapName,std::stoi(id));
        }
        for (const auto& i : table) {
            std::string oldNpcFile("../Maps/" + i.first + "/npclist.txt");
            std::ifstream oldNpcList(oldNpcFile);
            std::string newNpcFile("../Maps/" + i.first + "/tmpnpclist.txt");
            std::ofstream newNpcList(newNpcFile);
            if (oldNpcList.is_open()) {
                std::string _id, _x, _y, _state, line2;
                while (std::getline(oldNpcList, line2)) {
                    std::stringstream ss(line2);
                    std::getline(ss, _id, ',');
                    std::getline(ss, _x, ',');
                    std::getline(ss, _y, ',');
                    std::getline(ss, _state, ',');
                    for (auto j : table) {
                        if (std::stoi(_id) == i.second)
                            _state = "false";
                    }
                    newNpcList << _id << "," << _x << "," << _y << "," << _state << "\n";
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

void Game::load() {
    if(doesSaveFileExists()) {
        std::ifstream saveFile("../Saves/saves.txt");
        if (saveFile.is_open()) {
            std::string playersName, pokemonsName, mapName, xpos, ypos, money,_teamSize, hpCurrent, lvl, usesLeft,xp,playtime;
            std::getline(saveFile, playersName, ',');
            std::getline(saveFile, xpos, ',');
            std::getline(saveFile, ypos, ',');
            std::getline(saveFile, money, ',');
            std::getline(saveFile, _teamSize, ',');
            player.setName(playersName);
            player.setPosition(sf::Vector2f(std::stoi(xpos),std::stoi(ypos)));
            player.setMoney(std::stoi(money));
            player.team.clear();
            Pokemon **playersPokemon;
            int teamSize = std::stoi(_teamSize);
            playersPokemon = new Pokemon *[teamSize];
            for (int i = 0; i < teamSize; i++) {
                std::getline(saveFile, pokemonsName, ',');
                std::getline(saveFile, hpCurrent, ',');
                std::getline(saveFile, lvl, ',');
                std::getline(saveFile, xp, ',');
                playersPokemon[i] = new Pokemon(pokemonsName, std::stoi(lvl));
                playersPokemon[i]->loseHp(playersPokemon[i]->getMaxHp() - std::stoi(hpCurrent));
                playersPokemon[i]->setExpToNextLevel(std::stoi(xp));
                player.team.emplace_back(playersPokemon[i]);
                for (int j = 0; j < 4; j++) {
                    std::getline(saveFile, usesLeft, ',');
                    player.team[i]->getMoves(j)->setNUsage(std::stoi(usesLeft));
                }
            }
            std::getline(saveFile, mapName, ',');
            std::getline(saveFile, playtime, ',');
            previousSessionsPlayTime = std::stof(playtime);
            if (mapName == "POKEMON_CENTER") {
                changeState(GameState::STATE_POKEMON_CENTER);
                map = Map("tileset2.png", 27, 15, mapName);

            }else{
                changeState(GameState::STATE_MAP);
            }
        }
    }
}

