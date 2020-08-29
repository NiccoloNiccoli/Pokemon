//
// Created by Niccolò Niccoli on 08/07/2020.
//

#ifndef POKEMON_TILE_H
#define POKEMON_TILE_H

enum TypeOfTile{
    WALKABLE,
    NOT_WALKABLE,
    POKEMON_CENTER_DOOR,
    TALL_GRASS
};

class Tile {
public:
    Tile(int currentTileValue,const std::string& tileset);

    [[nodiscard]]int getValue() const;

    [[nodiscard]] TypeOfTile getType() const;

private:
    int value;
    TypeOfTile type;
};


#endif //POKEMON_TILE_H
