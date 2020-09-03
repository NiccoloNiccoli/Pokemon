//
// Created by Niccolò Niccoli on 22/06/2020.
//

#include <fstream>
#include <iostream>
#include "Type.h"
Type::Type(){

}
Type::Type(const std::string& type) {
    std::string currentType;
    std::ifstream file("../Pokemons/Types/" + type + ".txt");
    typeName = type;
    if (file.is_open()) {
        int nStrengths, nWeaknesses;
        file >>  nStrengths >> nWeaknesses;
        for(int i = 0; i < nStrengths; i++){
            file >> currentType;
            for (auto &c : currentType){
                c = toupper(c);
            }
            strongAgainst.push_back(currentType);
        }
        for(int i = 0; i < nWeaknesses; i++) {
            file >> currentType;
            for (auto &c : currentType) {
                c = toupper(c);
            }
            weakAgainst.push_back(currentType);
        }
    }else{
        throw std::runtime_error("Unable to open: ../Pokemons/Types/" + type + ".txt");
    }
    file.close();
    for (auto &c : typeName){
        c = toupper(c);
    }
}
const std::string &Type::getTypeName() const {
    return typeName;
}

float Type::checkTypeAdvantage(const Type& moveType,const std::vector<Type>& pokemonType) {
    float multiplier = 1.f;
   for(int i = 0; i < pokemonType.size(); i++) {
       for (const auto& j : moveType.strongAgainst)
           if (j == pokemonType[i].getTypeName())
               multiplier *= 2.f;
       for (const auto& j : moveType.weakAgainst)
           if (j == pokemonType[i].getTypeName())
               multiplier *= 0.5f;
   }
   return multiplier;
}