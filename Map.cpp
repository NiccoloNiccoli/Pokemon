//
// Created by Niccolò Niccoli on 08/07/2020.
//

#include <fstream>
#include <iostream>
#include "Map.h"
#include "GameState.h"
#include "Dice.h"

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
    font.loadFromFile("../pokemon_pixel_font.ttf");
    name.setFont(font);
    name.setPosition(box.getPosition().x + 7, box.getPosition().y - 9);

    if(mapName == "MappaDiProva"){
        averagePokemonLevel = 20;
        wildPokemons.emplace_back("Pikachu");
        wildPokemons.emplace_back("Squirtle");
        wildPokemons.emplace_back("Charmander");
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
    int currentTileValue;
    if(mapFile.is_open()){
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

        int column = (player.overworldSprite.getPosition().x + player.overworldSprite.getGlobalBounds().width/2)/16;
        int row = (player.overworldSprite.getPosition().y+ player.overworldSprite.getGlobalBounds().height/2)/16;
        if(tiles[column + row * 27].getType() == NOT_WALKABLE){
            player.overworldSprite.setPosition(oldPlayerPosition);
        }else if(tiles[column + row * 27].getType() == TALL_GRASS){
            //FIXME do it better
            if(GameState::getState()!=STATE_BATTLE){
                if(GameState::getTime() > 5.f + Dice::random(5)) {
                    //pick a random pokemon
                    Pokemon* wildPokemon = new Pokemon(wildPokemons[Dice::random(wildPokemons.size())], averagePokemonLevel + Dice::random(6) - 3);
#ifdef DEBUG
                    std::cout<<"You have found "<<wildPokemon->getName()<<" at level "<<wildPokemon->getLevel()<<std::endl;
#endif
                    GameState::changeState(STATE_BATTLE);
                    Battle::setWildPokemon(wildPokemon);
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