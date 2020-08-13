//
// Created by Niccolò Niccoli on 11/08/2020.
//

#ifndef POKEMON_STATEMAINMENU_H
#define POKEMON_STATEMAINMENU_H


#include "State.h"

class StateMainMenu : public State {
public:
    explicit StateMainMenu(Game *gamePtr);
    void draw(sf::RenderWindow& window) override;
    void changeState(State* nextState) override;
    void update() override;
    void handleInput(sf::Event event) override;
    GameState getStateName() override;
private:
    void loadInfo();
    int menuPageIndex = 0;
    int selectedItemIndex = 0;
    sf::Texture texture;
    AnimatedSprite sprite = AnimatedSprite(texture, 1280,720,4);
    sf::RectangleShape newGameBox = sf::RectangleShape(sf::Vector2f(350,60));
    sf::RectangleShape continueGameBox = sf::RectangleShape(sf::Vector2f(350, 120));

    //76,180
    sf::Font font;
    sf::Text newGame;
    sf::Text continueGame;
    sf::Text playersName;
    sf::Text playTime;
    sf::String playerInput = "";
    sf::Text insertName;

};

#endif //POKEMON_STATEMAINMENU_H
