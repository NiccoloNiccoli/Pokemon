//
// Created by Niccolò Niccoli on 10/08/2020.
//

#include <iostream>
#include "StatePokemonCenter.h"
#include "StatePauseMenu.h"

StatePokemonCenter::StatePokemonCenter(Game *gamePtr) : outsideMap(gamePtr->map){
    game = gamePtr;
   try {
        if (!buffer.loadFromFile("../SoundEffects/TeamHealed.wav")) {
            throw std::runtime_error("File not found: ../SoundEffects/TeamHealed.wav");
        }
        teamHealedSound.setBuffer(buffer);
        teamHealedSound.setLoop(false);
        if(!music.openFromFile("../SoundEffects/PokemonCenter.wav")){
            throw std::runtime_error("File not found: ../SoundEffects/PokemonCenter.wav");
        }
        music.setLoop(true);
        music.setVolume(20.f);
        music.play();
    }
    catch (const std::runtime_error &ex) {
        std::cerr << ex.what() << std::endl;
        exit(-1);
    }
    if(game->player.isAnyPokemonAlive()) {
        game->player.setPosition(200.f, 170.f);
    }else {
        game->player.setPosition(sf::Vector2f(206, 81));
        game->player.healTeam();
       teamHealedSound.play();
    }
    game->map = Map("tileset2.png",27,15,"POKEMON_CENTER");
    stateName = GameState ::STATE_POKEMON_CENTER;
}
void StatePokemonCenter::changeState(State *nextState) {
    if (nextState->getStateName() != GameState::STATE_BATTLE) {
        teamHealedSound.stop();
        State *tmpState = game->getCurrentState();
        game->setCurrentState(nextState);
        auto tmp = dynamic_cast<StatePauseMenu *>(game->getCurrentState());
        if (tmp != nullptr) {
            tmp->setPreviousState(tmpState);
            music.pause();
        } else {
            game->map = outsideMap;
            game->player.setPosition(game->map.findPokemonCenterDoor());
            music.stop();
            delete tmpState;
        }
    }
}

void StatePokemonCenter::draw(sf::RenderWindow &window) {
    window.draw(game->map);
    game->player.draw(window,game->player.getState());
    game->map.drawNPC(window);
}

void StatePokemonCenter::update() {
    game->player.move();
    game->map.checkCollisions(game->player);
}

void StatePokemonCenter::handleInput(sf::Event event, sf::RenderWindow &window) {
    if(event.type == sf::Event::KeyReleased){
        if(event.key.code == sf::Keyboard::Enter){
            if(game->map.lookForNearestEnemy(game->player) != nullptr){
                game->player.healTeam();
                teamHealedSound.play();
            }
        }
        if(event.key.code == sf::Keyboard::Escape){
            changeState(new StatePauseMenu(game));
        }
    }
}

GameState StatePokemonCenter::getStateName() {
    return stateName;
}

void StatePokemonCenter::playMusic() {
    music.play();
}


