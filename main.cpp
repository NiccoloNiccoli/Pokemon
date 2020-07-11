
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <ctime>
#include <fstream>
#include "Trainer.h"
#include "Pokemon.h"
#include "Battle.h"
#include "Map.h"
#include "GameState.h"
#include "debug.h"
#include "Player.h"
#include "Dice.h"

//C'è un fattore x3 a moltiplicare qualsiasi lunghezza
int main() {
    const int width = 1280, height = 720;
    sf::RenderWindow window(sf::VideoMode(width, height), "Pokemon", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    sf::View view(sf::FloatRect(0,0,width,height));
    view.setViewport(sf::FloatRect(0,0,3,3));
    srand(time(NULL));

    Map map("tileset1_1.png", 27, 15, "MappaDiProva");

Player player(0,40,70,"Niccolò");
Trainer rival(1,390,140,"Rival","blue.png");
Trainer lance(2, 144, 30, "Lance", "lance.png");
Trainer girl(3, 200, 150, "Giulia", "girl.png");
Battle battle(player);
//fixme - sono scomparsi i pulsanti della battaglia!!!!

        while(window.isOpen()){
            sf::Event event;
            while(window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if(GameState::getState()==STATE_BATTLE){
                    if(event.type == sf::Event::KeyReleased){
                        if(event.key.code == sf::Keyboard::Up){
                            battle.moveUp();
                        }else if(event.key.code == sf::Keyboard::Down){
                            battle.moveDown();
                        }else if(event.key.code == sf::Keyboard::Enter){
                            battle.refreshMenu(player,window);
                        }else if(event.key.code == sf::Keyboard::BackSpace){
                            battle.resetMenu();
                        }
                    }
                }else if(GameState::getState()==STATE_MAP){
                    if(event.type == sf::Event::KeyReleased){
                        if(event.key.code == sf::Keyboard::Enter){
                            player.fight(rival);
                        }
                    }
                }

            }
            window.clear();
            window.setView(view);
            if(GameState::getState()!=STATE_BATTLE) {
                player.move();

                /* if(position != sf::Vector2f(player.overworldSprite.getPosition()))
                     hasPlayerMoved = true;
                 else
                     hasPlayerMoved = false;
 */
                map.checkCollisions(player);

                //render game elements

                window.draw(map);
                window.draw(player.overworldSprite);
                window.draw(rival.overworldSprite);
                window.draw(lance.overworldSprite);
                window.draw(girl.overworldSprite);
                map.drawUI(window);

            }


           if(GameState::getState()==STATE_BATTLE){
               battle.battleEngine(window, player);
               }



            window.setView(window.getDefaultView());


    //render UI
            window.display();
    }
    return 0;
}