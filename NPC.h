//
// Created by Niccolò Niccoli on 13/08/2020.
//

#ifndef POKEMON_NPC_H
#define POKEMON_NPC_H

#include <SFML/Audio.hpp>
#include "Trainer.h"
class Action;
class NPC : public Trainer{
public:
    NPC(int id, int x, int y,bool canFight = true);
    void doAction();

    bool getIfIsFightable();
    void resetIsFightable();
    void nextAction();
    void hasBeenDefeated();

private:
    bool isFightable = true;
    Action* action = nullptr;
    sf::Texture inBattleSpriteTexture;
    sf::SoundBuffer buffer;
    sf::Sound defeatedSound;

};

class Action {
public:
    virtual ~Action()= default;
    virtual void doAction() = 0;
    virtual Action * nextAction() = 0;
protected:

    NPC* npc;

};

class Idle : public Action{
public:
    explicit Idle(NPC*  _npc);
    void doAction() override ;
    Action * nextAction() override;
private:
    float x,y;
};

class WalkVertically : public Action{
    //walk "up and down"
public:
    explicit WalkVertically(NPC* _npc);
    Action * nextAction() override;
    void doAction() override;
private:
    float yTargetTop, yTargetBottom,step = 0.5f;
};

class WalkHorizontally : public Action{
public:
    explicit WalkHorizontally(NPC* _npc);
    void doAction() override;
    Action * nextAction() override;
private:
    float xTargetLeft, xTargetRight,step = 0.5f;
};


#endif //POKEMON_NPC_H
