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

Pokemon::Pokemon(const std::string& pokemonName, unsigned int lvl){
  loadData(pokemonName);
  if(!texture.loadFromFile("../Pokemons/Textures/" + pokemonName + ".png")){
      //TODO handle error
  }
  texture.setSmooth(true);
  sprite.setTexture(texture);
  sprite.setScale(0.5f, 0.5f);
  //TODO load ability, if it's wild,
  level = lvl;
  maxHP = ((2*maxHP+31)*level/100)+level + 10;
  attack = ((2*attack+31)*level/100)+5;
  defense = ((2*defense+31)*level/100)+5;
  speed = ((2*speed+31)*level/100)+5;
  currentHP = maxHP;

}

bool Pokemon::loadData (const std::string& pokemonName){
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
        srand(time(NULL));
        for(int i = 0; i < 4 ; i++){
            int r = rand()%tmpMoves.size();
            moves.push_back(tmpMoves[r]);
            tmpMoves.erase(tmpMoves.begin() + r);
        }

        std::cout << id << " " <<  name << " " << maxHP << " " << attack << " " << defense << " " << speed << " ";
        for (auto i: type){
            std::cout << i.getTypeName() << " ";
        }


       std::cout <<  evolvingLevel << " " << nextFormId <<std::endl;
    }
}

void Pokemon::draw(sf::RenderWindow& window){
    window.draw(sprite);
}

bool Pokemon::doMove(Move& move, Pokemon& enemy, sf::RenderWindow& window) {
    int r1;
    r1 = rand() % 100;
    move.setNUsage(move.getNUsage()-1);
    std::cout<<move.getNUsage()<<" uses left"<<std::endl;
    if(r1 <= move.getAccuracy()){
        float modifier;
        int damage;
        float criticalHitMultiplier = 1.f;
        int randomFactor;
        float STAB = 1.f; //same type attack bonus
        int r;
        r = rand()%16;
        if(r==0){
            criticalHitMultiplier = 1.5f;
            std::cout<<"Critical hit!"<<std::endl;
        }
        randomFactor = ((rand()%25)+85);
        for(auto i : type)
            if(move.getType().getTypeName() == i.getTypeName())
                STAB = 1.5f;
        //type advantage mult.
        modifier = criticalHitMultiplier * randomFactor/100 * Type::checkTypeAdvantage(move.getType(), enemy.type) * STAB;
        std::cout<<"criticalMult. "<<criticalHitMultiplier<<" random factor "<<randomFactor<<" type adv. "<<Type::checkTypeAdvantage(move.getType(), enemy.type)<<" STAB "<<STAB<<std::endl;
        std::cout<<"modifier: "<<modifier<<std::endl;
        damage = (((2/5 * level + 2) * move.getPower() * attack/enemy.getDefense() + 2)/50 * modifier);
        std::cout<<"il danno inflitto è "<<damage<<std::endl;
        if(damage < 1)
            damage = 1;
        currentHP += currentHP*move.getHealingPercentage();
        if(currentHP > maxHP)
            currentHP = maxHP;
        enemy.loseHp(damage);
        std::cout<<enemy.name<<" has "<<enemy.currentHP<<" / "<<enemy.maxHP<<" HP"<<std::endl;
        move.playAnimation(window);
    }else{
        std::cerr<<"Missed!"<<std::endl;
        return false;
    }
}

int Pokemon::getDefense() const {
    return defense;
}

void Pokemon::loseHp(const int damage) {
    currentHP -= damage;
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
        std::cout << name << " is dead :(" << std::endl;
        currentHP = 0;
        alive = false;
    }
    return alive;
}
