//
// Created by Niccolò Niccoli on 10/07/2020.
//

#include <cmath>
#include <iostream>
#include "Player.h"

Player::Player(int id, int x, int y, std::string trainerName, std::string spriteName) : Trainer(id, x, y, trainerName, spriteName) {


}


void Player::move(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        overworldSprite.move(1.,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        overworldSprite.move(-1.,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        overworldSprite.move(0,-1.);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        overworldSprite.move(0,1.);
    xPosition = getXPosition();
    yPosition = getYPosition();
}

void Player::fight(Trainer &enemy) {
   if ((abs(xPosition - enemy.getXPosition())< 30.f) && (abs(yPosition - enemy.getYPosition()) < 40.f)){
#ifdef DEBUG
       std::cout<<"In battle range, xpos "<<xPosition<<" enemyxpos "<<enemy.getXPosition()<<std::endl;
#endif
   }

   }