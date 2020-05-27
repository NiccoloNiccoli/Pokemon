//
// Created by super on 22/05/2020.
//

#include "TileMap.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>

bool TileMap::load(const std::string &tilesetName, sf::Vector2u tileSize, unsigned int width, unsigned int height)
{
    if(!tileset.loadFromFile("../Textures/" + tilesetName))
        return false;
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(width * height * 4);
    std::vector<int> tiles;
    getMap("foglio2", tiles);
    for(unsigned int i = 0; i<width; ++i)
        for(unsigned int j = 0; j<height; ++j)
        {
            int tileNumber = tiles[i + j * width];

            int tu = tileNumber % (tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (tileset.getSize().x/ tileSize.x);

            sf::Vertex* quad = &vertices[(i + j * width) * 4];

            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i+1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i+1) * tileSize.x, (j+1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j+1) * tileSize.y);

            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu+1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    return true;
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &tileset;
    target.draw(vertices, states);
}

const int* TileMap::getMap(const std::string &mapName, std::vector<int>& tiles) {
 std::ifstream mapFile("../Maps/" + mapName + ".txt");
 int currentTile;
 if(mapFile.is_open()){
     while(mapFile >> currentTile)
         tiles.push_back(currentTile);

 }
}
