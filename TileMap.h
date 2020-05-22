//
// Created by super on 22/05/2020.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#ifndef POKEMON_TILEMAP_H
#define POKEMON_TILEMAP_H


class TileMap : public sf::Drawable, public sf::Transformable {
public:
    bool load(const std::string& tilesetName, sf::Vector2u tileSize, unsigned int width, unsigned int height);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    const int* getMap(const std::string& mapName, std::vector<int>& tiles);

    sf::VertexArray vertices;
    sf::Texture tileset;
};

//TODO mettere il nome della mappa(?) che sta in alto a sinistra per un paio di secondi e poi va via
#endif //POKEMON_TILEMAP_H
