//
// Created by super on 25/06/2020.
//

#ifndef POKEMON_BATTLE_H
#define POKEMON_BATTLE_H
#include <SFML/Graphics.hpp>

class Battle {
public:
    Battle();
    void draw(sf::RenderWindow& window);
    void chooseAction ();

    sf::Sprite background;
    sf::RectangleShape menuBox;
    sf::Text menuButtons[4];
private:
    int selectedItemIndex;
    sf::Font font;
    sf::Texture background_texture;

    void moveUp();
    void moveDown();

};


#endif //POKEMON_BATTLE_H
