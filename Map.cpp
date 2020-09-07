//
// Created by Niccolò Niccoli on 08/07/2020.
//

#include <fstream>
#include <iostream>
#include <cmath>
#include <sstream>
#include "Map.h"
#include "Dice.h"
#include "Game.h"
#include "NPC.h"

Map::Map(const std::string &tilesetName, unsigned int mapColumns, unsigned int mapRows, const std::string &mapName,
         sf::Vector2u tileSize_) {
    try {
        if (!tileset.loadFromFile("../Textures/" + tilesetName)) {
            throw std::runtime_error("File not found: ../Textures/" + tilesetName);
        }
        if (!font.loadFromFile("../pkmnem.ttf")) {
            throw std::runtime_error("File not found: ../pkmnem.ttf");
        }
        columns = mapColumns;
        rows = mapRows;
        tileSize = tileSize_;
        vertices.setPrimitiveType(sf::Quads);
        vertices.resize(columns * rows * 4);
        _name = mapName;
        loadMap(_name, tilesetName);
        for (unsigned int i = 0; i < columns; ++i)
            for (unsigned int j = 0; j < rows; ++j) {
                int tileNumber = tiles[i + j * columns].getValue();

                int tu = tileNumber % (tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (tileset.getSize().x / tileSize.x);

                sf::Vertex *quad = &vertices[(i + j * columns) * 4];

                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }

        //map ui
        if (!boxTexture.loadFromFile("../Textures/area_box.png")) {
            throw std::runtime_error("File not found: ../Textures/area_box.png");
        }
        box.setTexture(boxTexture);
        std::string tmp = _name;
        std::replace(tmp.begin(), tmp.end(), '_', ' ');
        name.setString(tmp);
        name.setCharacterSize(20);
        name.setFillColor(sf::Color::Black);
        name.setFont(font);
        name.setPosition(box.getPosition().x + 7, box.getPosition().y + 2);

        std::ifstream npclist("../Maps/" + _name + "/npclist.txt");
        if (npclist.is_open()) {
            std::string line, _id, _x, _y, isFightable;
            while (std::getline(npclist, line)) {
                std::stringstream ss(line);
                std::getline(ss, _id, ',');
                std::getline(ss, _x, ',');
                std::getline(ss, _y, ',');
                std::getline(ss, isFightable, ',');
                bool _isFightable = false;
                if (isFightable == "true")
                    _isFightable = true;
                npc.emplace_back(new NPC(std::stoi(_id),std::stoi(_x),std::stoi(_y), _isFightable));
            }
        }else{
            throw std::runtime_error("Unable to open:../Maps/" + _name + "/npclist.txt");
        }

        if (_name == "ROUTE_01") {
            averagePokemonLevel = 40;
            wildPokemons.emplace_back("Vileplume");
            wildPokemons.emplace_back("Umbreon");
            wildPokemons.emplace_back("Zangoose");
            wildPokemons.emplace_back("Pikachu");
        }
    } catch (const std::runtime_error &ex) {
        std::cerr << ex.what() << std::endl;
        exit(-1);
    }
}

void Map::loadMap(const std::string &__name,const std::string& tilesetName) {
    std::ifstream mapFile("../Maps/" + __name + "/" + __name + ".txt");
    if (mapFile.is_open()) {
        int currentTileValue;
        while (mapFile >> currentTileValue) {
            Tile currentTile(currentTileValue, tilesetName);
            tiles.push_back(currentTile);
        }

    }else{
        throw std::runtime_error("Unable to open: ../Maps/"+__name+"/"+__name+".txt");
    }
}


void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &tileset;
    target.draw(vertices, states);
}

void Map::checkCollisions(Trainer& player){
    if(oldPlayerPosition != player.getPosition()){
        if(player.getPosition().x < 0.f)
            player.setPosition(0.f, player.getPosition().y);
        if(player.getPosition().y < 0.f)
            player.setPosition(player.getPosition().x, 0.f);
        if((player.getPosition().x + player.getGlobalBounds().width) > columns*tileSize.x)
            player.setPosition(columns*tileSize.x - player.getGlobalBounds().width, player.getPosition().y);
        if(player.getPosition().y + player.getGlobalBounds().height > rows*tileSize.y)
            player.setPosition(player.getPosition().x, rows*tileSize.y - player.getGlobalBounds().height);

        //you can't walk on NPCs
        for(auto i : npc){
            if((((player.getPosition().x + player.getGlobalBounds().width) > i->getPosition().x) &&
               (player.getPosition().x < (i->getPosition().x + i->getGlobalBounds().width))) &&
            (((player.getPosition().y + player.getGlobalBounds().height) > i->getPosition().y) &&
             (player.getPosition().y < (i->getPosition().y + i->getGlobalBounds().height)))) {
                player.setPosition(oldPlayerPosition);
                if (player.getPosition() == sf::Vector2f(0, 0)) {
                    player.setPosition(40,70); //as defined in game.h
                    std::cerr<<"Position resetted"<<std::endl;
                }
            }
        }


        int column =static_cast<int>(player.getPosition().x + player.getGlobalBounds().width/2)/16;
        int row = static_cast<int>(player.getPosition().y+ player.getGlobalBounds().height/2)/16;
        if(tiles[column + row * 27].getType() == NOT_WALKABLE){
            player.setPosition(oldPlayerPosition);
        }else if(tiles[column + row * 27].getType() == TALL_GRASS){
            if(!(Game::getInstance()->checkState(GameState::STATE_BATTLE))){
                if(Game::getTime() > 5.f + Dice::random(5)) {
                    //pick a random pokemon
                    Battle::setWildPokemon(new Pokemon(wildPokemons[Dice::random(wildPokemons.size())], averagePokemonLevel + Dice::random(6) - 3));
                    Game::getInstance()->changeState(GameState::STATE_BATTLE);
                }
                //else you are already in a battle
            }

        }else if(tiles[column + row * 27].getType() == POKEMON_CENTER_DOOR){
            if(Game::getInstance()->checkState(GameState::STATE_POKEMON_CENTER)) {
                Game::getInstance()->changeState(GameState::STATE_MAP);
                restartTimer();
            }
            else
                Game::getInstance()->changeState(GameState::STATE_POKEMON_CENTER);
        }
    oldPlayerPosition = player.getPosition();
    }
}
void Map::drawUI(sf::RenderWindow &window) {
    if(timer.getElapsedTime().asSeconds() < 5.f){
        window.draw(box);
        window.draw(name);
    }
}

void Map::drawNPC(sf::RenderWindow &window) {
    for(auto i : npc){
        i->doAction();
        i->draw(window,i->getState());
    }
}

NPC *Map::lookForNearestEnemy(const Player& player) {
    NPC* nearestTrainer = nullptr;
    if(npc.size() > 0) {
        double distance = INT64_MAX; //distance = actualDistance^2, INT64_MAX = 9.22337e+018
        for (auto i : npc) {
            if (distance > (pow(player.getPosition().x - i->getPosition().x, 2) +
                            pow(player.getPosition().y - i->getPosition().y, 2))) {
                distance = pow(player.getPosition().x - i->getPosition().x, 2) +
                           pow(player.getPosition().y - i->getPosition().y, 2);
                nearestTrainer = i;
            }
        }
        if(distance > 1600) //if the distance between the player and the nearest enemy is more than 40 (player is wide 17) you can't fight with him
            nearestTrainer = nullptr;
    }
    return nearestTrainer;
}

const std::string &Map::getName() const {
    return _name;
}

void Map::restartTimer() {
    timer.restart();

}

sf::Vector2f Map::findPokemonCenterDoor() {
    int i = 0, j = 0;
    bool doorFound = false;
    while (i < columns && !doorFound) {
        j = 0;
        while (j < rows && !doorFound) {
            if (tiles[i + j * 27].getType() == POKEMON_CENTER_DOOR)
                doorFound = true;
            else
                j++;
        }
        if (!doorFound)
            i++;
    }
    return sf::Vector2f(i * tileSize.x, j * tileSize.y);
}

void Map::resetMap() {
    for(auto i : npc){
        i->resetIsFightable();
    }
}


