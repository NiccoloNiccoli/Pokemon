//
// Created by Niccolò Niccoli on 22/06/2020.
//

#include <fstream>
#include <iostream>
#include "Type.h"
Type::Type(){

}
Type::Type(const std::string& type) {
    int nStrengths, nWeaknesses;
    std::string currentType;
    std::ifstream file("../Pokemons/Types/" + type + ".txt");
    typeName = type;
    if (file.is_open()) {
        file >>  nStrengths >> nWeaknesses;
        for(int i = 0; i < nStrengths; i++){
            file >> currentType;
            strongAgainst.push_back(currentType);
        }
        for(int i = 0; i < nWeaknesses; i++){
            file >> currentType;
            weakAgainst.push_back(currentType);
        }
#ifdef DEBUG
        std::cout << typeName << " is strong against: ";
        for(auto i:strongAgainst)
            std::cout << i << " ";
        std::cout << "and weak against: ";
        for(auto i:weakAgainst)
            std::cout << i << " ";
#endif
    }
    for (auto &c : typeName){
        c = toupper(c);
    }
}
const std::string &Type::getTypeName() const {
    return typeName;
}

float Type::checkTypeAdvantage(Type moveType, std::vector<Type> pokemonType) {
    float multiplier = 1.f;
   for(int i = 0; i < pokemonType.size(); i++) {
       for (auto j : moveType.strongAgainst)
           if (j == pokemonType[i].getTypeName())
               multiplier *= 2.f;
       for (auto j : moveType.weakAgainst)
           if (j == pokemonType[i].getTypeName())
               multiplier *= 0.5f;
   }
   return multiplier;
}