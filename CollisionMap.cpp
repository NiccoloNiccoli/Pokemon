//
// Created by Niccolò Niccoli on 19/06/2020.
//
#include <fstream>
#include <vector>
#include <iostream>
#include "CollisionMap.h"

void CollisionMap::load(const std::string &collisionMapName){
    std::ifstream mapFile("../Maps/" + collisionMapName);
    if(mapFile.is_open()){
        int currentTile;
        while(mapFile >> currentTile)
            collTiles.push_back(currentTile);
    }
}
void CollisionMap::checkCollisions(Trainer& player,  const int screenWidth, const int screenHeight, sf::Vector2f position) {
    //std::cout<<player.overworldSprite.getPosition().x <<player.overworldSprite.getPosition().y<<std::endl;
    if(player.overworldSprite.getPosition().x < 0.f)
        player.overworldSprite.setPosition(0.f, player.overworldSprite.getPosition().y);
    if(player.overworldSprite.getPosition().y < 0.f)
        player.overworldSprite.setPosition(player.overworldSprite.getPosition().x, 0.f);
    if((player.overworldSprite.getPosition().x + player.overworldSprite.getGlobalBounds().width) > screenWidth/3)
        player.overworldSprite.setPosition(screenWidth/3 - player.overworldSprite.getGlobalBounds().width, player.overworldSprite.getPosition().y);
     if(player.overworldSprite.getPosition().y + player.overworldSprite.getGlobalBounds().height > screenHeight/3)
         player.overworldSprite.setPosition(player.overworldSprite.getPosition().x, screenHeight/3 - player.overworldSprite.getGlobalBounds().height);

     int column = (player.overworldSprite.getPosition().x + player.overworldSprite.getGlobalBounds().width/2)/16;
     int row = (player.overworldSprite.getPosition().y+ player.overworldSprite.getGlobalBounds().height/2)/16;
     if(collTiles[column + row * 27] == 2){
         player.overworldSprite.setPosition(position);
     }else if(collTiles[column + row * 27] == 1){
         //TODO-incontra un pokemon selvatico
         std::cout<<"Qui puoi trovare pokemon selvatici"<<std::endl;
     }else if(collTiles[column + row * 27]){
         //TODO-entra nel centro pokemon
         std::cout<<"Questo è il centro pokemon"<<std::endl;
     }
}