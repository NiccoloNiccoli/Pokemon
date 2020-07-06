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

    Map map("mappaDiProva");

Trainer player(0,40,70);
Battle battle(player, *::wildPokemon);
//fixme
bool hasPlayerMoved = false;

        while(window.isOpen()){
            sf::Event event;
            while(window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if(::isInBattle){
                    if(event.type == sf::Event::KeyReleased){
                        if(event.key.code == sf::Keyboard::Up){
                            battle.moveUp();
                        }else if(event.key.code == sf::Keyboard::Down){
                            battle.moveDown();
                        }else if(event.key.code == sf::Keyboard::Enter){
                            battle.refreshMenu(player, *::wildPokemon, window);
                        }else if(event.key.code == sf::Keyboard::BackSpace){
                            battle.resetMenu();
                        }
                    }
                }

            }
            window.clear();
            window.setView(view);
            if(!::isInBattle){
                sf::Vector2f position = player.overworldSprite.getPosition();
                player.move();
                if(position != sf::Vector2f(player.overworldSprite.getPosition()))
                    hasPlayerMoved = true;
                else
                    hasPlayerMoved = false;
                map.update(player, width, height, position, hasPlayerMoved);

                 //render game elements

                 window.draw(map.tileMap);
                 window.draw(player.overworldSprite);
                 if(map.timer.getElapsedTime().asSeconds() < 5.f){
                    window.draw(map.box);
                    window.draw(map.name);

                 }
            }


           if(::isInBattle){
               battle.battleEngine(window, player, *::wildPokemon);
               }



            window.setView(window.getDefaultView());


    //render UI
            window.display();
    }
    return 0;
}