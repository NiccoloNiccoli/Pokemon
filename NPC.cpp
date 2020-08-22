//
// Created by Niccolò Niccoli on 13/08/2020.
//

#include <iostream>
#include <cmath>
#include <fstream>
#include "NPC.h"
#include "Game.h"

NPC::NPC(int id, int x, int y,bool canFight) : Trainer(id, x, y), isFightable (canFight) {
    switch(id){
        case 1:
            action = new Chase(this);
            if(!inBattleSpriteTexture.loadFromFile("../Textures/inBattleSprite"+name+".png")) {
                //TODO
            }
            break;
        case 2 :
            action = new Idle(this);
            if(!inBattleSpriteTexture.loadFromFile("../Textures/inBattleSprite"+name+".png")) {
                //TODO
            }
            break;
        case 3:
            action = new Walk(this);
            if(!inBattleSpriteTexture.loadFromFile("../Textures/inBattleSpriteGirl.png")) {
                //TODO
            }
            break;
        case 4 :
            action = new Chase(this);
            break;
    }

    inBattleSprite = AnimatedSprite(inBattleSpriteTexture, 60 ,80, 2);
}

void NPC::doAction() {
    action->doAction();
}

bool NPC::getIfIsFightable() const {
    return isFightable;
}

void NPC::hasBeenDefeated() {
    isFightable = false;
    std::ofstream tmp("../Saves/tmp.txt", std::ios::app);
    if(tmp.is_open()){
        tmp << Game::getInstance()->map.getName() << " " << id << "\n";
    }
}

Idle::Idle(NPC *_npc) {
    npc = _npc;
    x = npc->getXPosition();
    y = npc->getYPosition();
}

void Idle::doAction() {
    //wanna rotate npc toward the player
    float xValue = Game::getInstance()->player.getXPosition() - x;
    float yValue = Game::getInstance()->player.getYPosition() - y;
    float i = sqrtf(xValue*xValue + yValue*yValue);
    int state = 0;
    if(xValue > 0 && yValue < 0){
        //I

        if(std::abs(xValue/i) < 0.7f) //0.7 = cos(45°)
            state = 4;
        else
            state = 2;
    }else if(xValue < 0 && yValue < 0){
        //II
        if(std::abs(xValue/i) < 0.7f)
            state = 4;
        else
            state = 6;
    }else if(xValue < 0 && yValue > 0){
        //III
        if(std::abs(xValue/i) < 0.7f)
            state = 0;
        else
            state = 6;
    }else if(xValue > 0 && yValue > 0){
        //IV
        if(std::abs(xValue/i) < 0.7f)
            state = 0;
        else
            state = 2;
    }
    npc->setState(state);
}

Walk::Walk(NPC *_npc) {
    npc = _npc;
    yTargetTop = npc->getYPosition() - 16*3;
    yTargetBottom = npc->getYPosition() + 16*3;
    npc->setState(1);
}



void Walk::doAction() {
  if(npc->getYPosition() == yTargetTop){
      npc->setState(1);
      step *= -1;
  }else if(npc->getYPosition() == yTargetBottom){
      npc->setState(5);
      step *= -1;
  }
  auto oldPosition = npc->overworldSprite.getPosition();
  npc->overworldSprite.move(0,step);


    if((((npc->overworldSprite.getPosition().x + npc->overworldSprite.getGlobalBounds().width) > Game::getInstance()->player.overworldSprite.getPosition().x) &&
        (npc->overworldSprite.getPosition().x < (Game::getInstance()->player.overworldSprite.getPosition().x + Game::getInstance()->player.overworldSprite.getGlobalBounds().width))) &&
       (((npc->overworldSprite.getPosition().y + npc->overworldSprite.getGlobalBounds().height) > Game::getInstance()->player.overworldSprite.getPosition().y) &&
        (npc->overworldSprite.getPosition().y < (Game::getInstance()->player.overworldSprite.getPosition().y + Game::getInstance()->player.overworldSprite.getGlobalBounds().height)))){
        npc->overworldSprite.setPosition(oldPosition);
        //FIXME change state when character is blocked
    }

  }


Chase::Chase(NPC *_npc) {

}

void Chase::doAction() {
//TODO A* algorithm
}

