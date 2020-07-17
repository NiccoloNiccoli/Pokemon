//
// Created by Niccolò Niccoli on 10/07/2020.
//

#include <cmath>
#include <iostream>
#include "Player.h"
#include "Battle.h"
#include "Dice.h"
#include "GameState.h"

Player::Player(int id, int x, int y, std::string trainerName) : Trainer(id, x, y) {
    name = trainerName;

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

void Player::fight(Trainer* enemy) {
    if(enemy != nullptr){
#ifdef DEBUG
        std::cout<<"In battle range, "<<enemy->getName()<<" is ready to fight"<<std::endl;
#endif
        Battle::setTrainer(enemy);
        GameState::changeState(STATE_BATTLE);
    }
   }

bool Player::catchPokemon(Pokemon* pokemon) {
    if(team.size()<6){
        if(Dice::random(10) != 0){
            //FIXME
            team.push_back(pokemon);
            Battle::changeBattleLog(pokemon->getName() + " is now in your team!");
#ifdef DEBUG
            std::cout<<pokemon->getName()<<" is now in your team "<<std::endl;
#endif
            return true;
        }else return false;
    }else{
        Battle::changeBattleLog("Your team is full!");
    }
        return false;
}
