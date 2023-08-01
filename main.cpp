#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Welcome Window");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
                return 0;
            }
            if (event.type == sf::Event::TextEntered){

            }
            if (event.type == sf::Event::KeyPressed){

            }
        }
        window.clear(sf::Color::White); // keep drawings below
        window.display();// keep drawings above
    }
    return 0;
}
