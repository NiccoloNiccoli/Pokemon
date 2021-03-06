//
// Created by Niccolò Niccoli on 10/08/2020.
//

#ifndef POKEMON_STATEPOKEMONCENTER_H
#define POKEMON_STATEPOKEMONCENTER_H

#include <SFML/Audio.hpp>
#include "State.h"

class StatePokemonCenter : public State {
public:
    explicit StatePokemonCenter(Game *gamePtr);
    void draw(sf::RenderWindow& window) override;
    void changeState(State* nextState) override;
    void update() override;
    void handleInput(sf::Event event, sf::RenderWindow &window) override;
    GameState getStateName() override;
    void playMusic() override ;
private:
    //i need these to set properly the map when i leave the center
    Map outsideMap = Map ("tileset1_1.png",27,15,"ROUTE_01");
    sf::SoundBuffer buffer;
    sf::Sound teamHealedSound;



};


#endif //POKEMON_STATEPOKEMONCENTER_H
