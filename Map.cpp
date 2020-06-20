//
// Created by super on 19/06/2020.
//

#include "Map.h"

Map::Map(){
    tileMap.load("tileset1_1.png", sf::Vector2u(16,16), 27, 15);
    //se non esiste il tileset lanciare un'eccezione
    collisionMap.load("collisionMap.txt");
}

void Map::update(Trainer& player,  const int screenWidth, const int screenHeight, sf::Vector2f position){
    collisionMap.checkCollisions(player, screenWidth, screenHeight, position);
}
