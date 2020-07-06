//
// Created by Niccolò Niccoli on 22/05/2020.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#ifndef POKEMON_TILEMAP_H
#define POKEMON_TILEMAP_H


class TileMap : public sf::Drawable, public sf::Transformable {
public:
    bool load(const std::string& tilesetName, sf::Vector2u tileSize, unsigned int width, unsigned int height, const std::string& mapName);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    const int* getMap(const std::string& mapName, std::vector<int>& tiles);

    sf::VertexArray vertices;
    sf::Texture tileset;
    std::string mapName;
};

#endif //POKEMON_TILEMAP_H
