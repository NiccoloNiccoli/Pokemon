//
// Created by Niccolò Niccoli on 23/08/2020.
//

#include <iostream>
#include "StatePauseMenu.h"

void StatePauseMenu::draw(sf::RenderWindow &window) {
    window.clear(sf::Color::Blue);
    for(int i = 0; i <3 ;i++)
    window.draw(buttons[i]);
}

StatePauseMenu::StatePauseMenu(Game *gamePtr) {
    game = gamePtr;
    try {
        if (!font.loadFromFile("../pkmnem.ttf")) {
            throw std::runtime_error("File not found: ../pkmnem.ttf");
        }
        if (!music.openFromFile("../SoundEffects/Menu.wav")) {
            throw std::runtime_error("File not found: ../SoundEffects/Menu.wav");
        }
        music.setLoop(true);
        music.setVolume(50.f);
        music.play();
    }
    catch(const std::runtime_error& ex){
        std::cerr<<ex.what()<<std::endl;
    }
    for(int i = 0; i < 3; i++){
        buttons[i].setFont(font);
        buttons[i].setFillColor(sf::Color::White);
        buttons[i].setPosition(static_cast<int>(1280/6 - 17), static_cast<int>(240/5 + i * 240/5 ));
    }
    buttons[0].setString("BACK");
    buttons[0].setFillColor(sf::Color::Red);
    buttons[1].setString("SAVE");
    buttons[2].setString("QUIT");
    stateName = GameState :: STATE_PAUSE_MENU;
}

void StatePauseMenu::changeState(State *nextState) {
    if(nextState->getStateName() != GameState::STATE_BATTLE){
        State *tmpState = game->getCurrentState();
        game->setCurrentState(nextState);
        music.stop();
        game->getCurrentState()->playMusic();
        delete tmpState;
    }
}

void StatePauseMenu::handleInput(sf::Event event, sf::RenderWindow &window) {
    if(event.type == sf::Event::KeyReleased){
        if(event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W){
            buttons[abs(selectedButton)%3].setFillColor(sf::Color::White);
            selectedButton--;
            if(selectedButton == -1)
                selectedButton = 2;
            buttons[abs(selectedButton)%3].setFillColor(sf::Color::Red);
        }else if(event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S){
            buttons[selectedButton%3].setFillColor(sf::Color::White);
            selectedButton++;
            if(selectedButton == 3)
                selectedButton = 0;
           buttons[selectedButton%3].setFillColor(sf::Color::Red);
        }else if(event.key.code == sf::Keyboard::Enter){
            switch(selectedButton){
                case 0:
                   changeState(previousState);
                    break;
                case 1:
                    game->save();
                    break;
                case 2:
                    music.stop();
                    window.close();
            }
        }else if(event.key.code == sf::Keyboard::Escape){
            changeState(previousState);
        }
    }
}

void StatePauseMenu::update() {

}

GameState StatePauseMenu::getStateName() {
    return stateName;
}

void StatePauseMenu::setPreviousState(State *state) {
    previousState = state;
}

void StatePauseMenu::playMusic() {
    music.play();
}
