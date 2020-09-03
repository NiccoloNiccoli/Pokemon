
#include<stdexcept>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <ctime>
#include "Battle.h"
#include "Game.h"

//C'è un fattore x3 a moltiplicare qualsiasi lunghezza
int main() {
        const int width = 1280, height = 720;
        sf::RenderWindow window(sf::VideoMode(width, height), "Pokemon", sf::Style::Titlebar | sf::Style::Close);
        window.setFramerateLimit(60);
        sf::View view(sf::FloatRect(0, 0, width, height));
        view.setViewport(sf::FloatRect(0, 0, 3, 3));
        srand(time(nullptr));

        Game *game = Game::getInstance();
        while (window.isOpen()) {
            sf::Event event{};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                game->handleInput(event, window);
            }
            window.clear();
            window.setView(view);


            game->update();
            game->drawCurrentScene(window);
            window.setView(window.getDefaultView());

            window.display();

        }
        delete game;
        return 0;
    }
