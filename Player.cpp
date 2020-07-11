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

bool Player::catchPokemon(Pokemon& pokemon) {
    if(team.size()<6){
        int r = rand()%10;
        if(r != 0){
            //FIXME
            team.push_back(pokemon);
#ifdef DEBUG
            std::cout<<pokemon.getName()<<" is now in your team "<<std::endl;
#endif
            return true;
        }else return false;
    }else
        return false;
}
