//
// Created by Niccolò Niccoli on 13/08/2020.
//

#ifndef POKEMON_NPC_H
#define POKEMON_NPC_H


#include "Trainer.h"
class Action;
class NPC : public Trainer{
public:
    NPC(int id, int x, int y,bool canFight = true);
    void doAction();

    bool getIfIsFightable() const;

    void hasBeenDefeated();

private:
    bool isFightable = true;
    Action* action = nullptr;
};

class Action {
public:
    virtual ~Action(){};
    virtual void doAction() = 0;

protected:

    NPC* npc;

};

class Idle : public Action{
public:
    explicit Idle(NPC*  _npc);
    void doAction() override ;
private:
    float x,y;
};

class Walk : public Action{
    //walk "up and down"
public:
    explicit Walk(NPC* _npc);

    void doAction() override;
private:
    float yTargetTop, yTargetBottom,step = 0.5f;
};

class Chase : public Action{
public:
    Chase(NPC* _npc);
    void doAction() override;
};


#endif //POKEMON_NPC_H
