//
// Created by Niccolò Niccoli on 08/07/2020.
//

#ifndef POKEMON_MAP_H
#define POKEMON_MAP_H


#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Trainer.h"
#include "debug.h"

class Map : public sf::Drawable, public sf::Transformable {
public:
    Map(const std::string& tilesetName, unsigned int mapColumns, unsigned int mapRows,
        const std::string& mapName, sf::Vector2u tileSize_ = sf::Vector2u(16,16));
    void drawUI(sf::RenderWindow& window);
    void checkCollisions(Trainer& player);
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void loadMap(const std::string& mapName);
    unsigned int columns;
    unsigned int rows;
    sf::Vector2f oldPlayerPosition = sf::Vector2f(0,0);
    sf::Vector2u tileSize;
    sf::VertexArray vertices;
    sf::Texture tileset;
    std::vector<Tile> tiles;

    //map ui
    sf::Sprite box;
    sf::Texture boxTexture;
    sf::Font font;
    sf::Text name;
    sf::Clock timer;

    unsigned int averagePokemonLevel;
    std::vector<std::string> wildPokemons;
    //TODO vector con gli NPC che si trovano sulla mappa
};


#endif //POKEMON_MAP_H
