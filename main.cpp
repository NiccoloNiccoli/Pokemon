#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <ctime>
#include <fstream>
#include "TileMap.h"
#include "Trainer.h"
#include "Map.h"
#include "Pokemon.h"
#include "Battle.h"


//C'è un fattore x3 a moltiplicare qualsiasi lunghezza

int main() {
    const int width = 1280, height = 720;
    sf::RenderWindow window(sf::VideoMode(width, height), "Pokemon", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    sf::View view(sf::FloatRect(0,0,width,height));
    view.setViewport(sf::FloatRect(0,0,3,3));
    //FIXME togliere i vari magic numbers


    Map map("mappaDiProva");


Trainer player(0,40,70);
Pokemon pika ("pikachu", 34);
Battle battle;

        while(window.isOpen()){
            sf::Event event;
            while(window.pollEvent(event))
                if(event.type == sf::Event::Closed){
                    window.close();
                }

            window.clear();



            sf::Vector2f position = player.overworldSprite.getPosition();
            player.move();
            map.update(player, width, height, position);

            //render game elements
            window.setView(view);
            window.draw(map.tileMap);
            window.draw(player.overworldSprite);
            if(map.timer.getElapsedTime().asSeconds() < 5.f){
                window.draw(map.box);
                window.draw(map.name);
                window.draw(pika.sprite);
                battle.chooseAction();
               battle.draw(window);


            }

            window.setView(window.getDefaultView());


    //render UI
            window.display();
    }
    return 0;
}
