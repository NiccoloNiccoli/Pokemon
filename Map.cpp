//
// Created by super on 19/06/2020.
//

#include "Map.h"

Map::Map(const std::string& mapName){
    tileMap.load("tileset1_1.png", sf::Vector2u(16,16), 27, 15, mapName);
    //se non esiste il tileset lanciare un'eccezione
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

void Map::update(Trainer& player,  const int screenWidth, const int screenHeight, sf::Vector2f position){
    collisionMap.checkCollisions(player, screenWidth, screenHeight, position);
}
