//
// Created by Calvi on 8/2/2023.
//

#ifndef DSAPROJECT3_WINDOW_H
#define DSAPROJECT3_WINDOW_H

#endif //DSAPROJECT3_WINDOW_H

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

class Window {
private:
    sf::RenderWindow window;
public:
    Window(int width, int height, string name);
    void DisplayWindow();
};

Window::Window(int width, int height, string name) {
    window.create(sf::VideoMode(width, height), name);
}

void Window::DisplayWindow() {
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::TextEntered){

            }
            if (event.type == sf::Event::KeyPressed){

            }
        }
        window.clear(sf::Color::White); // keep drawings below

        window.display();// keep drawings above
    }
}
