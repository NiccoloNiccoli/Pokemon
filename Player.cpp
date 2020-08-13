//
// Created by Niccolò Niccoli on 10/07/2020.
//

#include <cmath>
#include <iostream>
#include "Player.h"
#include "Battle.h"
#include "Dice.h"
#include "Game.h"

Player::Player(int id, int x, int y, std::string trainersName) : Trainer(id, x, y) {
   setName(trainersName);

}


void Player::move(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        overworldSprite.move(1.,0);
        state = 3;
        isStateUpdated=false;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        overworldSprite.move(-1.,0);
        state = 7;
        isStateUpdated=false;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        overworldSprite.move(0,-1.);
        state = 5;
        isStateUpdated=false;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        overworldSprite.move(0,1.);
        state = 1;
        isStateUpdated=false;
    } else
        if(!isStateUpdated){
            state -=1;
            isStateUpdated=true;
        }
    xPosition = getXPosition();
    yPosition = getYPosition();

}

void Player::fight(NPC* enemy) {
    if(enemy != nullptr && enemy->getIfIsFightable()){
#ifdef DEBUG
        std::cout<<"In battle range, "<<enemy->getName()<<" is ready to fight"<<std::endl;
#endif
        Battle::setTrainer(enemy);
        Game::getInstance()->changeState(GameState::STATE_BATTLE);
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

void Player::setName(std::string playersName) {
    name = playersName;
}

int Player::winMoney(NPC *opponent) {
    if((opponent->getIfIsFightable())){
        Trainer::winMoney(opponent);
        opponent->hasBeenDefeated();
    }

}
