//
// Created by super on 22/06/2020.
//

#ifndef POKEMON_TYPE_H
#define POKEMON_TYPE_H


#include <string>
#include <vector>


class Type {
public:
    Type();
    Type(const std::string& type);

    const std::string &getTypeName() const;


private:
    std::string typeName;
    std::vector<std::string> strongAgainst;
    std::vector<std::string> weakAgainst;



};


#endif //POKEMON_TYPE_H