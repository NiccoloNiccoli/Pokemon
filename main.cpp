#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <fstream>
#include "TileMap.h"

//C'è un fattore x3 a moltiplicare qualsiasi lunghezza

class TmpPlayer {
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


int main() {
    //FIXME-DELETE THIS e sistemare un po' il resto
    TmpPlayer player(sf::Vector2f(40,90), sf::Vector2f(20,20), sf::Color::Magenta);
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
    TileMap map;
    if(!map.load("tileset1_1.png", sf::Vector2u(16,16), 27, 15))
        return -1;

//XXX
std::vector<int> collTiles;
std::string mapName ("collisionMap");
std::ifstream mapFile("../Maps/" + mapName + ".txt");
    if(mapFile.is_open()){
        int currentTile;
        while(mapFile >> currentTile)
            collTiles.push_back(currentTile);

    }
//XXX
        while(window.isOpen()){
            sf::Event event;
            while(window.pollEvent(event))
                if(event.type == sf::Event::Closed){
                    window.close();
                }

            window.clear();
//FIXME-farlo più ordinato
sf::Vector2f position = player.rect.getPosition();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                player.rect.move(1.,0);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                player.rect.move(-1.,0);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                player.rect.move(0,-1.);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                player.rect.move(0,1.);
            //XXX
            player.update();
            player.rect.setFillColor(sf::Color::Red);
            if(player.rect.getPosition().x < 0.f)
                player.rect.setPosition(0.f, player.rect.getPosition().y);
            if(player.rect.getPosition().y < 0.f)
                player.rect.setPosition(player.rect.getPosition().x, 0.f);
            if((player.rect.getPosition().x + player.rect.getGlobalBounds().width) > width/3)
                player.rect.setPosition(width/3 - player.rect.getGlobalBounds().width, player.rect.getPosition().y);
            if(player.rect.getPosition().y + player.rect.getGlobalBounds().height > height/3)
                player.rect.setPosition(player.rect.getPosition().x, height/3 - player.rect.getGlobalBounds().height);

            //std::cout << "X: " << player.rect.getPosition().x + player.rect.getGlobalBounds().width/2 << " Y: " << player.rect.getPosition().y +player.rect.getGlobalBounds().height/2<< std::endl;
            int column = (player.rect.getPosition().x /*+ player.rect.getGlobalBounds().width*/)/16;
            int row = (player.rect.getPosition().y /*+ player.rect.getGlobalBounds().height*/)/16;
            if(collTiles[column + row * 27] == 2){
            player.rect.setPosition(position);
            }else if(collTiles[column + row * 27] == 1){
                //TODO-incontra un pokemon selvatico
                std::cout<<"Qui puoi trovare pokemon selvatici"<<std::endl;
            }else if(collTiles[column + row * 27]){
                //TODO-entra nel centro pokemon(?)
                std::cout<<"Questo è il centro pokemon"<<std::endl;
            }
            //XXX
            //render game elements
            window.setView(view);
            window.draw(map);
            window.draw(player.rect);
            window.draw(placeName);
            window.draw(text);
            window.setView(window.getDefaultView());

    //render UI
            window.display();
    }
    return 0;
}
