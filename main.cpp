#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <fstream>
#include "TileMap.h"
#include "Trainer.h"
#include "Map.h"

//C'è un fattore x3 a moltiplicare qualsiasi lunghezza

/*class TmpPlayer {
public:
    sf::RectangleShape rect;
  float bottom, top, right, left;

  TmpPlayer(sf::Vector2f position, sf::Vector2f size, sf::Color color){
      rect.setPosition(position);
      rect.setSize(size);
      rect.setFillColor(color);
  }

  void update(){
      bottom = rect.getPosition().y + rect.getSize().y;
      left = rect.getPosition().x;
      right = rect.getPosition().x + rect.getSize().x;
      top = rect.getPosition().y;
  }
};
*/

int main() {
    //FIXME-DELETE THIS e sistemare un po' il resto
    //TmpPlayer player(sf::Vector2f(40,90), sf::Vector2f(20,20), sf::Color::Magenta);
    //END DELETE quando ci sarà il personaggio giocabile
    const int width = 1280, height = 720;
    sf::RenderWindow window(sf::VideoMode(width, height), "Pokemon", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    sf::View view(sf::FloatRect(0,0,width,height));
    view.setViewport(sf::FloatRect(0,0,3,3));
    //FIXME togliere i vari M A G I C   N U M B E R S

    sf::RectangleShape placeName(sf::Vector2f(100, 20));
    sf::Text text;
    text.setString("Sample");
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    sf::Font font;
    font.loadFromFile("../pokemon_pixel_font.ttf");
    text.setFont(font);
    text.setPosition(placeName.getPosition().x + 4,placeName.getPosition().y - 5); //2 e -5 sono offset tirati fuori un po' a casa
    Map map;


//XXX
Trainer player(0,40,70);
    //XXX
        while(window.isOpen()){
            sf::Event event;
            while(window.pollEvent(event))
                if(event.type == sf::Event::Closed){
                    window.close();
                }

            window.clear();
//FIXME-farlo più ordinato


            //XXX

            //XXX
            sf::Vector2f position = player.overworldSprite.getPosition();
            player.move();
            map.update(player, width, height, position);

            //render game elements
            window.setView(view);
            window.draw(map.tileMap);
            window.draw(player.overworldSprite);
            window.draw(placeName);
            window.draw(text);
            window.setView(window.getDefaultView());

    //render UI
            window.display();
    }
    return 0;
}
