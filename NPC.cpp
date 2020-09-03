//
// Created by Niccolò Niccoli on 13/08/2020.
//

#include <iostream>
#include <cmath>
#include <fstream>
#include "NPC.h"
#include "Game.h"

NPC::NPC(int id, int x, int y,bool canFight) : Trainer(id, x, y), isFightable (canFight) {
try {
        if (!buffer.loadFromFile("../SoundEffects/FoeDefeated.wav")) {
            throw std::runtime_error("File not found: ../SoundEffects/FoeDefeated.wav");
        }
        defeatedSound.setBuffer(buffer);
        defeatedSound.setLoop(false);
    switch (id) {
        case 1:
            action = new Idle(this);
            if (!inBattleSpriteTexture.loadFromFile("../Textures/inBattleSprite" + spriteName)) {
                throw std::runtime_error("File not found: ../Textures/inBattleSprite" + spriteName);
            }
            break;
        case 2 :
            action = new WalkHorizontally(this);
            if (!inBattleSpriteTexture.loadFromFile("../Textures/inBattleSprite" + spriteName)) {
                throw std::runtime_error("File not found: ../Textures/inBattleSprite" + spriteName);
            }
            break;
        case 3:
            action = new WalkVertically(this);
            if (!inBattleSpriteTexture.loadFromFile("../Textures/inBattleSprite" + spriteName)) {
                throw std::runtime_error("File not found: ../Textures/inBattleSprite" + spriteName);
            }
            break;
        default:
            action = new Idle(this);
    }
    inBattleSprite = AnimatedSprite(inBattleSpriteTexture, 60 ,80, 2);
}
catch (const std::runtime_error &ex) {
    std::cerr << ex.what() << std::endl;
    exit(-1);
}
}

void NPC::doAction() {
    action->doAction();
}

bool NPC::getIfIsFightable(){
   if(!isFightable)
       defeatedSound.play();
    return isFightable;
}

void NPC::hasBeenDefeated() {
    isFightable = false;
    std::ofstream tmp("../Saves/tmp.txt", std::ios::app);
    if(tmp.is_open()){
        tmp << Game::getInstance()->map.getName() << " " << id << "\n";
    }
    tmp.close();
    nextAction();
}

void NPC::nextAction() {
    auto tmp = action;
    action = action->nextAction();
    delete tmp;
}

void NPC::resetIsFightable() {
    isFightable = true;
}

Idle::Idle(NPC *_npc) {
    npc = _npc;
    x = npc->getPosition().x;
    y = npc->getPosition().y;
}

void Idle::doAction() {
    //rotate npc toward the player
    float xValue = static_cast<float>(Game::getInstance()->player.getPosition().x - x);
    float yValue = static_cast<float>(Game::getInstance()->player.getPosition().y - y);
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

Action * Idle::nextAction() {
    return new Idle(npc);
}

WalkVertically::WalkVertically(NPC *_npc) {
    npc = _npc;
    yTargetTop = npc->getPosition().y - 16*3;
    yTargetBottom = npc->getPosition().y + 16*3;
    npc->setState(1);
}



void WalkVertically::doAction() {


    if(npc->getPosition().y == yTargetTop){
        npc->setState(1);
        step *= -1;
    }else if(npc->getPosition().y == yTargetBottom){
        npc->setState(5);
        step *= -1;
    }
    auto oldPosition = npc->getPosition();
  npc->move(0,step);


    if((((npc->getPosition().x + npc->getGlobalBounds().width) > Game::getInstance()->player.getPosition().x) &&
        (npc->getPosition().x < (Game::getInstance()->player.getPosition().x + Game::getInstance()->player.getGlobalBounds().width))) &&
       (((npc->getPosition().y + npc->getGlobalBounds().height) > Game::getInstance()->player.getPosition().y) &&
        (npc->getPosition().y < (Game::getInstance()->player.getPosition().y + Game::getInstance()->player.getGlobalBounds().height)))){
        npc->setPosition(oldPosition);
        if(npc->getState() == 1)
            npc->setState(0);
        else if(npc->getState() == 5)
            npc->setState(4);
    }else{
        if(npc->getState()==0)
            npc->setState(1);
        else if(npc->getState()==4)
            npc->setState(5);
    }
  }

Action * WalkVertically::nextAction() {
    return new Idle(npc);
}


WalkHorizontally::WalkHorizontally(NPC *_npc) {
    npc = _npc;
    xTargetLeft = npc->getPosition().x - 16*3;
    xTargetRight = npc->getPosition().x + 16*3;
    npc->setState(3);
}

void WalkHorizontally::doAction() {
    if(npc->getPosition().x == xTargetLeft){
        npc->setState(3);
        step *= -1;
    }else if(npc->getPosition().x == xTargetRight){
        npc->setState(7);
        step *= -1;
    }
    auto oldPosition = npc->getPosition();
    npc->move(step,0);


    if((((npc->getPosition().x + npc->getGlobalBounds().width) > Game::getInstance()->player.getPosition().x) &&
        (npc->getPosition().x < (Game::getInstance()->player.getPosition().x + Game::getInstance()->player.getGlobalBounds().width))) &&
       (((npc->getPosition().y + npc->getGlobalBounds().height) > Game::getInstance()->player.getPosition().y) &&
        (npc->getPosition().y < (Game::getInstance()->player.getPosition().y + Game::getInstance()->player.getGlobalBounds().height)))){
        npc->setPosition(oldPosition);
        if(npc->getState() == 3)
            npc->setState(2);
        else if(npc->getState() == 7)
            npc->setState(6);
    }else{
        if(npc->getState()==2)
            npc->setState(3);
        else if(npc->getState()==6)
            npc->setState(7);
    }
}

Action *WalkHorizontally::nextAction() {
    return new Idle(npc);
}

