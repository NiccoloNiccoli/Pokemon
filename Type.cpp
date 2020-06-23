//
// Created by super on 22/06/2020.
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

        std::cout << typeName << " is strong against: ";
        for(auto i:strongAgainst)
            std::cout << i << " ";
        std::cout << "and weak against: ";
        for(auto i:weakAgainst)
            std::cout << i << " ";
    }
}
const std::string &Type::getTypeName() const {
    return typeName;
}
//TODO controllare contro quali tipi fa danno x2 e contro quali x0.5