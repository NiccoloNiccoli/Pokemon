//
// Created by Niccolò Niccoli on 22/06/2020.
//

#ifndef POKEMON_TYPE_H
#define POKEMON_TYPE_H


#include <string>
#include <vector>

class Type {
public:
    Type();
    explicit Type(const std::string& type);

    [[nodiscard]] const std::string &getTypeName() const;
    static float checkTypeAdvantage(const Type& moveType,const std::vector<Type>& pokemonType) ;

private:
    std::string typeName;
    std::vector<std::string> strongAgainst;
    std::vector<std::string> weakAgainst;
};


#endif //POKEMON_TYPE_H
