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
#include "Battle.h"

Pokemon::Pokemon(const std::string& pokemonName, unsigned int lvl){
  loadData(pokemonName);
    if(!texture.loadFromFile("../Pokemons/Textures/" + pokemonName + ".png")){
        //TODO handle error
    }
    sprite = AnimatedSprite(texture,82,81,1);
  //TODO load ability, if it's wild,
  if(lvl <= 100 && lvl >= 1)
    level = lvl;
  else
      level = 1;
  updateStats();
  currentHP = maxHP;
  expToNextLevel = pow(level,3) * 4/5 - 16000; //TODO this must be saved :)
  std::cerr<<expToNextLevel<<std::endl;

}

void Pokemon::loadData (const std::string& pokemonName){
    std::string type1, type2;
    std::ifstream file("../Pokemons/" + pokemonName + ".txt");
    if(file.is_open()){
       file >> id >> name >> maxHP >> attack >> defense >> speed >> type1 >> type2 >> evolvingLevel >> nextFormName;
        Type tmpType(type1);
        type.push_back(tmpType);
        //FIRST TYPE CANNOT BE NULL. AT LEAST ONE TYPE MUST EXISTS
        if(type2 != "NULL"){
            Type tmpType(type2);
            type.push_back(tmpType);

        }
        std::string currentMove_string;
        int i = 0;
        while(file >> currentMove_string){
            moves[i] = new Move(currentMove_string);
            i++;
        }
#ifdef DEBUG
        std::cout << id << " " <<  name << " " << maxHP << " " << attack << " " << defense << " " << speed << " ";
#endif
        for (auto i: type){
            std::cout << i.getTypeName() << " ";
        }
#ifdef DEBUG
       std::cout <<  evolvingLevel << " " << nextFormName <<std::endl;
#endif
    }
}

void Pokemon::draw(sf::RenderWindow& window, int row){
    sprite.draw(window,1000,row);
}

int Pokemon::doMove(Move* move, Pokemon &enemy) {
    move->setNUsage(move->getNUsage() - 1);
#ifdef DEBUG
    std::cout << move->getNUsage() << " uses left" << std::endl;
#endif
    Battle::setLastMoveUsed(move);
    if (Dice::random(100) <= move->getAccuracy()) {
        float modifier;
        int damage;
        float criticalHitMultiplier = 1.f;
        int randomFactor;
        float STAB = 1.f; //same type attack bonus
        if (Dice::random(16) == 0) {
            criticalHitMultiplier = 1.5f;
#ifdef DEBUG
            std::cout << "Critical hit!" << std::endl;
#endif
        }
            randomFactor = Dice::random(85, 100);
            for (auto i : type)
                if (move->getType().getTypeName() == i.getTypeName())
                    STAB = 1.5f;
            //type advantage mult.
            modifier =
                    criticalHitMultiplier * randomFactor / 100 * Type::checkTypeAdvantage(move->getType(), enemy.type) *
                    STAB;
#ifdef DEBUG
            std::cout << "criticalMult. " << criticalHitMultiplier << " random factor " << randomFactor << " type adv. "
                      << Type::checkTypeAdvantage(move->getType(), enemy.type) << " STAB " << STAB << std::endl;
            std::cout << "modifier: " << modifier << std::endl;
#endif
            damage = powf(((2 / 5 * level + 2) * move->getPower() * attack / enemy.getDefense() + 100) / 50, 1.5) *
                     modifier; //^1.5 l'ho aggiunto io per rendere il danno più interessante
#ifdef DEBUG
            std::cout << "il danno inflitto è " << damage << std::endl;
#endif
            if (damage < 1)
                damage = 1;
        enemy.loseHp(damage);
            currentHP += move->getHealingPercentage() * abs(enemy.maxHP - enemy.currentHP);
            if (currentHP > maxHP)
                currentHP = maxHP;

#ifdef DEBUG
            std::cout << enemy.name << " has " << enemy.currentHP << " / " << enemy.maxHP << " HP" << std::endl;
#endif
            //TODO play anim
            bool crit = false, supEff = false, notEff = false;
            if (criticalHitMultiplier == 1.5f)
                crit = true;
            if (Type::checkTypeAdvantage(move->getType(), enemy.type) >= 2)
                supEff = true;
            else if (Type::checkTypeAdvantage(move->getType(), enemy.type) <= 0.5f)
                notEff = true;
            Battle::setFlags(crit, notEff, supEff);
            return damage;
        } else {
            return 0;
        }
}

int Pokemon::getDefense() const {
    return defense;
}

int Pokemon::loseHp(const int damage) {
    currentHP -= damage;
    isAlive();
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
        currentHP = 0;
        Battle::changeBattleLog(name + " fainted!");
        alive = false;
    }
    return alive;
}

int Pokemon::getAttack() const {
    return attack;
}

int Pokemon::gainEXP(Pokemon *enemy) {
    if(level < 100) {
        int expGained = level * enemy->level * 20; //formula semplificata a partire da quella presente sulla wiki
        while (expToNextLevel - expGained < 0 && level < 100) {
            expGained -= expToNextLevel;
            level++;
            updateStats();
#ifdef DEBUG
            std::cout<<"level up!"<<std::endl;
#endif
            expToNextLevel = pow(level,3) * 4/5;
            if(level > evolvingLevel)
                evolve();
        }
        expToNextLevel -= expGained;
        return expGained;
    } else
        return 0;
}

void Pokemon::updateStats() {
    int deltaHP = maxHP;
    maxHP = ((2*maxHP+48)*level/100)+level + 10;
    attack = ((2*attack+48)*level/100)+5;
    defense = ((2*defense+48)*level/100)+5;
    speed = ((2*speed+48)*level/100)+5;
    deltaHP -= maxHP;
    currentHP += abs(deltaHP);
}

void Pokemon::evolve() {
      Pokemon tmp(nextFormName,level);
      id = tmp.id;
      maxHP = tmp.maxHP;
      currentHP = tmp.currentHP;
      attack = tmp.attack;
      defense = tmp.defense;
      speed = tmp.speed;
      type = tmp.type;
      level = tmp.level; //non dovrebbe essere necessario
      alive = tmp.alive;
      expToNextLevel = tmp.expToNextLevel;
      name = tmp.name;
      if(!texture.loadFromFile("../Pokemons/Textures/" + name + ".png")){
        //TODO handle error
      }
     sprite = AnimatedSprite(texture,82,81,1);


}

void Pokemon::heal() {
    currentHP = maxHP;
    alive = true;
    for(int i = 0; i < 4; i++)
        moves[i]->setNUsage(moves[i]->getMaxUses());
}

int Pokemon::getExpToNextLevel() const {
    return expToNextLevel;
}
