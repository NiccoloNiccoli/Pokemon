//
// Created by Niccolò Niccoli on 19/06/2020.
//

#include "Map.h"

Map::Map(const std::string& mapName){
    if(!tileMap.load("tileset1_1.png", sf::Vector2u(16,16), 27, 15, mapName)){
        //TODO handle error
    }
    collisionMap.load("collisionMap.txt");
    boxTexture.loadFromFile("../Textures/boxTexture.png");
    box.setScale(0.5f, 0.5f);
    box.setTexture(boxTexture);
    name.setString(mapName);
    name.setCharacterSize(30);
    name.setFillColor(sf::Color::Black);
    font.loadFromFile("../pokemon_pixel_font.ttf");
    name.setFont(font);
    name.setPosition(box.getPosition().x + 7, box.getPosition().y - 9); //2 e -5 sono offset tirati fuori un po' a casa

}

void Map::update(Trainer& player,  const int screenWidth, const int screenHeight, sf::Vector2f position, bool hasPlayerMoved){
    collisionMap.checkCollisions(player, screenWidth, screenHeight, position, hasPlayerMoved);
}
