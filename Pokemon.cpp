//
// Created by super on 22/06/2020.
//

//Textures are 256x256 px

#include <fstream>
#include <iostream>
#include "Pokemon.h"
#include <ctime>
#include <random>

Pokemon::Pokemon(const std::string& pokemonName, unsigned int level){
  loadData(pokemonName);
  texture.loadFromFile("../Pokemons/Textures/" + pokemonName + ".png");
  texture.setSmooth(true);
  sprite.setTexture(texture);
  sprite.setScale(0.5f, 0.5f);
  //TODO load type, ability, moves, if it's wild,

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
        for(int i = 0; i < 3; i++){
            int r = rand()%tmpMoves.size();
            moves.push_back(tmpMoves[r]);
            tmpMoves.erase(tmpMoves.begin() + r);
        }

        std::cout << id << " " <<  name << " " << maxHP << " " << attack << " " << defense << " " << speed << " ";
        for (auto i: type){
            std::cout << i.getTypeName() << " ";
        }


       std::cout <<  evolvingLevel << " " << nextFormId <<std::endl;
       //TODO (?)
    }
}
/*
int id;
std::string name;
sf::Sprite sprite;
sf::Texture texture;
int currentHP;
int maxHP;
int attack;
int defense;
int speed;
//TODO Type, Ability, Moves
bool isWild;
int level;
int evolvingLevel;
int nextFormId;*/