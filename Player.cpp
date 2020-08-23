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
   if(!inBattleSpriteTexture.loadFromFile("../Textures/inBattleSpritePlayer.png")) {
        //TODO
   }
   inBattleSprite = AnimatedSprite(inBattleSpriteTexture, 80 ,80, 4);
}


void Player::move(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        overworldSprite.move(1.,0);
        state = 3;
        isStateUpdated=false;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        overworldSprite.move(-1.,0);
        state = 7;
        isStateUpdated=false;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        overworldSprite.move(0,-1.);
        state = 5;
        isStateUpdated=false;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
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
        Battle::setTrainer(enemy);/*
        Game::getInstance()->battle.setSentenceIndex(0);
        Game::getInstance()->battle.changeFeedbackSentence();*/
        Game::getInstance()->changeState(GameState::STATE_BATTLE);
    }
   }

bool Player::catchPokemon(Pokemon* pokemon) {
        if(Dice::random(10) != 0){
            //FIXME
            team.push_back(pokemon);
            Battle::changeBattleLog(pokemon->getName() + " is now in your team!");
#ifdef DEBUG
            std::cout<<pokemon->getName()<<" is now in your team "<<std::endl;
#endif
            return true;
        }else return false;
}

void Player::setName(std::string playersName) {
    name = playersName;
}

int Player::winMoney(NPC *opponent) {
    int prize = 0;
    if((opponent->getIfIsFightable())){
        prize = Trainer::winMoney(opponent);
        opponent->hasBeenDefeated();
    }
    return prize;
}

bool Player::isAnyPokemonAlive() {
    bool returnValue = false;
   for(int i = 0; i < team.size(); i++)
       if(team[i]->isAlive())
           returnValue = true;
    return returnValue;
}
