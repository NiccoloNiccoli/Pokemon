//
// Created by super on 19/06/2020.
//

#ifndef POKEMON_MAP_H
#define POKEMON_MAP_H


#include "TileMap.h"
#include "CollisionMap.h"
#include <SFML/Graphics.hpp>

class Map {
public:
    void update(Trainer& player, const int screenWidth, const int screenHeight, sf::Vector2f position);
    TileMap tileMap;
    CollisionMap collisionMap;

    Map();
};


#endif //POKEMON_MAP_H
