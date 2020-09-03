//
// Created by Niccolò Niccoli on 10/07/2020.
//

#include <cmath>
#include <iostream>
#include "Player.h"
#include "Battle.h"
#include "Dice.h"
#include "Game.h"

Player::Player(int id, int x, int y, const std::string& trainersName) : Trainer(id, x, y) {
   setName(trainersName);
   try {

       if (!inBattleSpriteTexture.loadFromFile("../Textures/inBattleSpritePlayer.png")) {
           throw std::runtime_error("File not found: ../Textures/inBattleSpritePlayer.png");
       }
       inBattleSprite = AnimatedSprite(inBattleSpriteTexture, 80 ,80, 4);
   }
   catch (const std::runtime_error &ex) {
       std::cerr << ex.what() << std::endl;
       exit(-1);
   }
}


void Player::move(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        Trainer::move(1.,0);
        state = 3;
        isStateUpdated=false;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        Trainer::move(-1.,0);
        state = 7;
        isStateUpdated=false;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        Trainer::move(0,-1.);
        state = 5;
        isStateUpdated=false;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        Trainer::move(0,1.);
        state = 1;
        isStateUpdated=false;
    } else
        if(!isStateUpdated){
            state -=1;
            isStateUpdated=true;
        }
    xPosition = getPosition().x;
    yPosition = getPosition().y;

}

void Player::fight(NPC* enemy) {
    if(enemy != nullptr && enemy->getIfIsFightable()){
        Battle::setTrainer(enemy);
        Game::getInstance()->changeState(GameState::STATE_BATTLE);
    }
   }

bool Player::catchPokemon(Pokemon* pokemon) {
        if(Dice::random(10) != 0){
            team.push_back(pokemon);
            return true;
        }else return false;
}

void Player::setName(const std::string& playersName) {
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
