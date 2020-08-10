//
// Created by Niccolò Niccoli on 08/07/2020.
//

#include <fstream>
#include <iostream>
#include <cmath>
#include "Map.h"
#include "Dice.h"
#include "Game.h"

Map::Map(const std::string &tilesetName, unsigned int mapColumns, unsigned int mapRows, const std::string &mapName,
         sf::Vector2u tileSize_) {
    if(!tileset.loadFromFile("../Textures/" + tilesetName)){
        //TODO handle error
    }
    columns = mapColumns;
    rows = mapRows;
    tileSize=tileSize_;
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(columns * rows * 4);
    loadMap(mapName);
    for(unsigned int i = 0; i<columns; ++i)
        for(unsigned int j = 0; j<rows; ++j)
        {
            int tileNumber = tiles[i + j * columns].getValue();

            int tu = tileNumber % (tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (tileset.getSize().x/ tileSize.x);

            sf::Vertex* quad = &vertices[(i + j * columns) * 4];

            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i+1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i+1) * tileSize.x, (j+1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j+1) * tileSize.y);

            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu+1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }

    //map ui
    boxTexture.loadFromFile("../Textures/boxTexture.png");
    box.setScale(0.5f, 0.5f);
    box.setTexture(boxTexture);
    name.setString(mapName);
    name.setCharacterSize(30);
    name.setFillColor(sf::Color::Black);
    font.loadFromFile("../pkmnem.ttf");
    name.setFont(font);
    name.setPosition(box.getPosition().x + 7, box.getPosition().y);
    name.setScale(0.8f,0.8f);

    if(mapName == "MappaDiProva"){
        averagePokemonLevel = 20;
        wildPokemons.emplace_back("Pikachu");
        wildPokemons.emplace_back("Squirtle");
        wildPokemons.emplace_back("Charmander");
        Trainer* rival;
        rival = new Trainer(1,390,140);
        npc.emplace_back(rival);
        Trainer* lance;
        lance = new Trainer(2, 144, 30);
        npc.emplace_back(lance);
        Trainer* girl01;
        girl01 = new Trainer (3, 200, 150);
        npc.emplace_back(girl01);
#ifdef DEBUG
        for(auto i : npc)
            std::cout<<i->getName()<<std::endl;
#endif
    }

#ifdef DEBUG
        std::cout<<"Here you can find: "<<std::endl;
        for(auto i : wildPokemons)
            std::cout<<i<<std::endl;
    #endif

    timer.restart();
}

void Map::loadMap(const std::string &mapName) {
    std::ifstream mapFile("../Maps/" + mapName + ".txt");
    if(mapFile.is_open()){
        int currentTileValue;
        while(mapFile >> currentTileValue){
            Tile currentTile(currentTileValue);
            tiles.push_back(currentTile);
        }

    }
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &tileset;
    target.draw(vertices, states);
}

void Map::checkCollisions(Trainer& player){
    if(oldPlayerPosition != player.overworldSprite.getPosition()){
        //FIXME collision with pokemon center
        if(player.overworldSprite.getPosition().x < 0.f)
            player.overworldSprite.setPosition(0.f, player.overworldSprite.getPosition().y);
        if(player.overworldSprite.getPosition().y < 0.f)
            player.overworldSprite.setPosition(player.overworldSprite.getPosition().x, 0.f);
        if((player.overworldSprite.getPosition().x + player.overworldSprite.getGlobalBounds().width) > columns*tileSize.x)
            player.overworldSprite.setPosition(columns*tileSize.x - player.overworldSprite.getGlobalBounds().width, player.overworldSprite.getPosition().y);
        if(player.overworldSprite.getPosition().y + player.overworldSprite.getGlobalBounds().height > rows*tileSize.y)
            player.overworldSprite.setPosition(player.overworldSprite.getPosition().x, rows*tileSize.y - player.overworldSprite.getGlobalBounds().height);

        //you can't walk on NPCs
        for(auto i : npc){
            if((((player.overworldSprite.getPosition().x + player.overworldSprite.getGlobalBounds().width) > i->overworldSprite.getPosition().x) &&
               (player.overworldSprite.getPosition().x < (i->overworldSprite.getPosition().x + i->overworldSprite.getGlobalBounds().width))) &&
            (((player.overworldSprite.getPosition().y + player.overworldSprite.getGlobalBounds().height) > i->overworldSprite.getPosition().y) &&
             (player.overworldSprite.getPosition().y < (i->overworldSprite.getPosition().y + i->overworldSprite.getGlobalBounds().height))))

                player.overworldSprite.setPosition(oldPlayerPosition);
        }


        int column = (player.overworldSprite.getPosition().x + player.overworldSprite.getGlobalBounds().width/2)/16;
        int row = (player.overworldSprite.getPosition().y+ player.overworldSprite.getGlobalBounds().height/2)/16;
        if(tiles[column + row * 27].getType() == NOT_WALKABLE){
            player.overworldSprite.setPosition(oldPlayerPosition);
        }else if(tiles[column + row * 27].getType() == TALL_GRASS){
            //FIXME do it better
            if(!(Game::getInstance()->checkState(GameState::STATE_BATTLE))){
                if(Game::getTime() > 5.f + Dice::random(5)) {
                    //pick a random pokemon
                    Pokemon* wildPokemon = new Pokemon(wildPokemons[Dice::random(wildPokemons.size())], averagePokemonLevel + Dice::random(6) - 3);
#ifdef DEBUG
                    std::cout<<"You have found "<<wildPokemon->getName()<<" at level "<<wildPokemon->getLevel()<<std::endl;
#endif
                    Battle::setWildPokemon(wildPokemon);
                    Game::getInstance()->changeState(GameState::STATE_BATTLE);
                }
                //else you are already in a battle
#ifdef DEBUG
                std::cout<<"Qui puoi trovare pokemon selvatici"<<std::endl;
#endif
            }

        }else if(tiles[column + row * 27].getType() == POKEMON_CENTER_DOOR){
            //TODO-entra nel centro pokemon
#ifdef DEBUG
            std::cout<<"Questo è il centro pokemon"<<std::endl;
#endif
        }
    oldPlayerPosition = player.overworldSprite.getPosition();
    }
}
void Map::drawUI(sf::RenderWindow &window) {
    if(timer.getElapsedTime().asSeconds() < 5.f){
        window.draw(box);
        window.draw(name);
    }
}

void Map::drawNPC(sf::RenderWindow &window) {
    for(auto i : npc)
        window.draw(i->overworldSprite);
}

Trainer *Map::lookForNearestEnemy(const Player& player) {
    Trainer* nearestTrainer = nullptr;
    if(npc.size() > 0) {
        double distance = INT64_MAX; //distance = actualDistance^2, INT64_MAX = 9.22337e+018
        for (auto i : npc) {
            if (distance > (pow(player.overworldSprite.getPosition().x - i->overworldSprite.getPosition().x, 2) +
                            pow(player.overworldSprite.getPosition().y - i->overworldSprite.getPosition().y, 2))) {
                distance = pow(player.overworldSprite.getPosition().x - i->overworldSprite.getPosition().x, 2) +
                           pow(player.overworldSprite.getPosition().y - i->overworldSprite.getPosition().y, 2);
                nearestTrainer = i;
            }
        }
        if(distance > 1600) //if the distance between the player and the nearest enemy is more than 40 (player is wide 17) you can't fight with him
            nearestTrainer = nullptr;
    }
    return nearestTrainer;
}
