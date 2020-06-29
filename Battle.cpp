//
// Created by Niccolò Niccoli on 25/06/2020.
//

#include "Battle.h"
Battle::Battle(){
   if(!background_texture.loadFromFile("../Textures/background.png")){
       //TODO handle error
   }
    background.setTexture(background_texture);
    background.setScale(0.35f,0.35f);
    sf::RectangleShape tmpBox (sf::Vector2f(120.f,100.f));
    tmpBox.setFillColor(sf::Color::White);
    tmpBox.setPosition(sf::Vector2f(300, 135));
    menuBox = tmpBox;
    if(!font.loadFromFile("../pokemon_pixel_font.ttf")){
        //TODO handle error
    }
    //initializing buttons "FIGHT", "SWAP", "CATCH", "RUN"
    menuButtons[0].setFont(font);
    menuButtons[0].setFillColor(sf::Color::Red);
    menuButtons[0].setString("FIGHT");
    menuButtons[0].setPosition(sf::Vector2f(menuBox.getPosition().x + 10, menuBox.getPosition().y + 10));
    menuButtons[0].setScale(0.8f, 0.8f);

    menuButtons[1].setFont(font);
    menuButtons[1].setFillColor(sf::Color::Black);
    menuButtons[1].setString("CATCH");
    menuButtons[1].setPosition(sf::Vector2f(menuBox.getPosition().x + 65, menuBox.getPosition().y + 10));
    menuButtons[1].setScale(0.8f, 0.8f);


    menuButtons[2].setFont(font);
    menuButtons[2].setFillColor(sf::Color::Black);
    menuButtons[2].setString("SWAP");
    menuButtons[2].setPosition(sf::Vector2f(menuBox.getPosition().x + 10, menuBox.getPosition().y + 50));
    menuButtons[2].setScale(0.8f, 0.8f);


    menuButtons[3].setFont(font);
    menuButtons[3].setFillColor(sf::Color::Black);
    menuButtons[3].setString("RUN");
    menuButtons[3].setPosition(sf::Vector2f(menuBox.getPosition().x + 65, menuBox.getPosition().y + 50));
    menuButtons[3].setScale(0.8f, 0.8f);

    selectedItemIndex = 0;

}

void Battle::draw(sf::RenderWindow &window) {
    window.draw(background);
    window.draw(menuBox);
    for(auto i : menuButtons)
        window.draw(i);
}

void Battle::moveUp(){
        menuButtons[abs(selectedItemIndex)%4].setFillColor(sf::Color::Black);
        selectedItemIndex--;
        menuButtons[abs(selectedItemIndex)%4].setFillColor(sf::Color::Red);
}

void Battle::moveDown() {
        menuButtons[selectedItemIndex%4].setFillColor(sf::Color::Black);
        selectedItemIndex++;
        menuButtons[selectedItemIndex%4].setFillColor(sf::Color::Red);
}

void Battle::chooseAction() {
    //TODO scorrere il menù con i tasti
    sf::Event event;
    /*sf::Event::KeyReleased;
    switch(event.type){

    }
    switch(event.key.code){
        case sf::Keyboard::Up:
                moveUp();
            break;
        case sf::Keyboard::Down:
                moveDown();
            break;
        case sf::Keyboard::Left:
                moveUp();
                moveUp();
            break;
        case sf::Keyboard::Right:
                moveDown();
                moveDown();
            break;


    }*/
    if(event.type == (sf::Event::KeyReleased)){
        switch(event.type){
            case sf::Keyboard::Up:
                moveUp();
                break;
            case sf::Keyboard::Down:
                moveDown();
                break;
            case sf::Keyboard::Left:
                moveUp();
                moveUp();
                break;
            case sf::Keyboard::Right:
                moveDown();
                moveDown();
                break;
        }
    }
}