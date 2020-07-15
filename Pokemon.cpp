//
// Created by Niccolò Niccoli on 22/06/2020.
//

//Textures are 256x256 px

#include <fstream>
#include <iostream>
#include "Pokemon.h"
#include <ctime>
#include <random>
#include "Type.h"
#include "Dice.h"

Pokemon::Pokemon(const std::string& pokemonName, unsigned int lvl){
  loadData(pokemonName);
    if(!texture.loadFromFile("../Pokemons/Textures/" + pokemonName + ".png")){
        //TODO handle error
    }
  texture.setSmooth(true);
  sprite.setTexture(texture);
  sprite.setScale(0.5f, 0.5f);
  //TODO load ability, if it's wild,
  if(lvl <= 100 && lvl >= 1)
    level = lvl;
  else
      level = 1;
  maxHP = ((2*maxHP+31)*level/100)+level + 10;
  attack = ((2*attack+31)*level/100)+5;
  defense = ((2*defense+31)*level/100)+5;
  speed = ((2*speed+31)*level/100)+5;
  currentHP = maxHP;

}

void Pokemon::loadData (const std::string& pokemonName){
    std::string type1, type2;
    std::ifstream file("../Pokemons/" + pokemonName + ".txt");
    if(file.is_open()){
       file >> id >> name >> maxHP >> attack >> defense >> speed >> type1 >> type2 >> evolvingLevel >> nextFormId;
        Type tmpType(type1);
        type.push_back(tmpType);
        //FIRST TYPE CANNOT BE NULL. AT LEAST ONE TYPE MUST EXISTS
        if(type2 != "NULL"){
            Type tmpType(type2);
            type.push_back(tmpType);

        }
        std::vector<Move> tmpMoves;
        std::string currentMove_string;
        while(file >> currentMove_string){
            Move currentMove (currentMove_string);
            tmpMoves.push_back(currentMove);
        }
        for(int i = 0; i < 4 ; i++){
            int r = Dice::random(tmpMoves.size());
            moves.push_back(tmpMoves[r]);
            tmpMoves.erase(tmpMoves.begin() + r);
        }
#ifdef DEBUG
        std::cout << id << " " <<  name << " " << maxHP << " " << attack << " " << defense << " " << speed << " ";
#endif
        for (auto i: type){
            std::cout << i.getTypeName() << " ";
        }
#ifdef DEBUG
       std::cout <<  evolvingLevel << " " << nextFormId <<std::endl;
#endif
    }
}

void Pokemon::draw(sf::RenderWindow& window){
    window.draw(sprite);
}

int Pokemon::doMove(Move& move, Pokemon& enemy, sf::RenderWindow& window) {
    move.setNUsage(move.getNUsage()-1);
#ifdef DEBUG
    std::cout<<move.getNUsage()<<" uses left"<<std::endl;
#endif
    if(Dice::random(100) <= move.getAccuracy()){
        float modifier;
        int damage;
        float criticalHitMultiplier = 1.f;
        int randomFactor;
        float STAB = 1.f; //same type attack bonus
        if(Dice::random(16)==0){
            criticalHitMultiplier = 1.5f;
#ifdef DEBUG
            std::cout<<"Critical hit!"<<std::endl;
#endif
        }
        randomFactor = Dice::random(85,110);
        for(auto i : type)
            if(move.getType().getTypeName() == i.getTypeName())
                STAB = 1.5f;
        //type advantage mult.
        modifier = criticalHitMultiplier * randomFactor/100 * Type::checkTypeAdvantage(move.getType(), enemy.type) * STAB;
#ifdef DEBUG
        std::cout<<"criticalMult. "<<criticalHitMultiplier<<" random factor "<<randomFactor<<" type adv. "<<Type::checkTypeAdvantage(move.getType(), enemy.type)<<" STAB "<<STAB<<std::endl;
        std::cout<<"modifier: "<<modifier<<std::endl;
#endif
        damage = (((2/5 * level + 2) * move.getPower() * attack/enemy.getDefense() + 2)/50 * modifier);
#ifdef DEBUG
        std::cout<<"il danno inflitto è "<<damage<<std::endl;
#endif
        if(damage < 1)
            damage = 1;
        currentHP += currentHP*move.getHealingPercentage();
        if(currentHP > maxHP)
            currentHP = maxHP;
        enemy.loseHp(damage);
#ifdef DEBUG
        std::cout<<enemy.name<<" has "<<enemy.currentHP<<" / "<<enemy.maxHP<<" HP"<<std::endl;
#endif
        move.playAnimation(window);
        return damage;
    }else{
#ifdef DEBUG
        std::cerr<<"Missed!"<<std::endl;
#endif
        return -1;
    }
}

int Pokemon::getDefense() const {
    return defense;
}

int Pokemon::loseHp(const int damage) {
    currentHP -= damage;
    return currentHP;
}

int Pokemon::getCurrentHp() const {
    return currentHP;
}

int Pokemon::getMaxHp() const {
    return maxHP;
}

const std::string &Pokemon::getName() const {
    return name;
}

int Pokemon::getSpeed() const {
    return speed;
}

int Pokemon::getLevel() const {
    return level;
}

bool Pokemon::isAlive(){
    if(currentHP <= 0) {
#ifdef DEBUG
        std::cout << name << " is dead :(" << std::endl;
#endif
        currentHP = 0;
        alive = false;
    }
    return alive;
}

int Pokemon::getAttack() const {
    return attack;
}
