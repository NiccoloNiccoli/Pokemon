#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main() {
    int width = 800, height = 600;
    sf::RenderWindow window(sf::VideoMode(width, height), "Pokemon");
    window.setFramerateLimit(60);
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event))
            if(event.type == sf::Event::Closed){
                window.close();
            }
        window.clear();

        //draw everything here ( window.draw(...); )

        window.display();
    }
    return 0;
}
