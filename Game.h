//
// Created by Niccolò Niccoli on 10/08/2020.
//

#ifndef POKEMON_GAME_H
#define POKEMON_GAME_H


#include <SFML/System/Clock.hpp>
#include<SFML/Graphics.hpp>
#include "Map.h"
#include "Battle.h"

class State; //To avoid circular dependency
enum class GameState{
    STATE_MAP,
    STATE_BATTLE,
    STATE_POKEMON_CENTER
};
class Game {
public:
   static Game* getInstance();
    void changeState(GameState nextGameState);
    void drawCurrentScene(sf::RenderWindow& window);
    void update();
    void handleInput(sf::Event event);

    State *getCurrentState() const;
    void setCurrentState(State *currentState);
    bool checkState(GameState state);

    static float getTime();
    static void resetTimer();


    //FIXME
    Map map = Map("tileset1_1.png", 27, 15, "MappaDiProva");
    Player player = Player(0,40,70,"Niccolò");
    Battle battle = Battle(player);
private:
    Game();
    static Game* instance;
    State* createPointer(GameState state);
    static sf::Clock timer;
    State* currentState;


};


#endif //POKEMON_GAME_H
