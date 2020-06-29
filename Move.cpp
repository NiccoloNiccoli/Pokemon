//
// Created by Niccolò Niccoli on 23/06/2020.
//

#include <fstream>
#include <iostream>
#include "Move.h"

Move::Move(const std::string& moveName){
    std::ifstream file("../Pokemons/Moves/" + moveName + ".txt");
    if (file.is_open()) {
        std::string tmpType_string;
        name = moveName;
        file >> power >> healingPercentage >> n_usage >> tmpType_string >> accuracy;
        Type tmpType(tmpType_string);
        type = tmpType;
        std::cout << " *bling blong* " << name << " Power: " << power << " Healing percentage: " << healingPercentage << " Number of usage: " << n_usage <<
        " Type: " << type.getTypeName() << " Accuracy: " << accuracy << std::endl;
    }
}

const std::string &Move::getName() const {
    return name;
}