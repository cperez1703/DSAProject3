#ifndef DSAPROJECT3_WINDOW_H
#define DSAPROJECT3_WINDOW_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "HashMap.h"
#include "Artist.h"

using namespace std;

class Window {
private:
    sf::RenderWindow window;
    string name;
    int width;
    int height;
    sf::Font font;
    void setText(sf::Text &text, float x, float y);
    void DisplayRedBlack();
    void DisplayHashmap();
    HashMap hashMap;
    Artist artist;
    string genre; // Add the genre member variable

public:
    Window(int width, int height, string name, string genre);
    void DisplayWindow();
    void displayArtistsByGenre(sf::RenderWindow& window, HashMap& hashMap, sf::Font& font, int width, int height, const string& genre);

};

void setText(sf::Text text, float d, int offset);

Window::Window(int width, int height, string name, string genre) {
    this->name = name;
    this->width = width;
    this->height = height;
    this->genre = genre;
    font.loadFromFile("OpenSans-Regular.ttf");
    //artist = Artist("", "", genre, "", ""); // Initialize the artist member with empty values
}

void Window::setText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

void Window::DisplayWindow() {
    window.create(sf::VideoMode(width, height), name);
    sf::Text title("Undercover Artists", font, 100);
    title.setFillColor(sf::Color::Black);
    title.setOutlineColor(sf::Color::White);
    title.setOutlineThickness(3);
    setText(title, width/2.0f, height/3.0f);

    sf::Text redBlack("Red-Black Tree", font, 50);
    redBlack.setFillColor(sf::Color::White);
    setText(redBlack, width/2.0f, height/2.0f);

    sf::Text hashmap("Hash Map", font, 50);
    hashmap.setFillColor(sf::Color::White);
    setText(hashmap, width/2.0f, height/3.0f*2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::TextEntered) {

            }
            if (event.type == sf::Event::KeyPressed) {

            }
            if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased) {
                if (redBlack.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    window.close();
                    DisplayRedBlack();
                }
                if (hashmap.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    window.close();
                    DisplayHashmap();
                }
            }
        }
        window.clear(sf::Color::Transparent);
        window.draw(title);
        window.draw(redBlack);
        window.draw(hashmap);
        window.display();
    }
}

void Window::DisplayRedBlack() {
    sf::RenderWindow redBlack;
    redBlack.create(sf::VideoMode(width, height), "Red-Black");

    sf::Text back("Return", font, 50);
    back.setFillColor(sf::Color::White);
    setText(back, width/10.0f, height/20.0f);

    while (redBlack.isOpen()) {
        sf::Event event;
        while (redBlack.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                redBlack.close();
            }
            if (event.type == sf::Event::TextEntered) {

            }
            if (event.type == sf::Event::KeyPressed) {

            }
            if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased) {
                if (back.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    redBlack.close();
                    DisplayWindow();
                }
            }
        }
        redBlack.clear(sf::Color::Transparent);
        redBlack.draw(back);
        redBlack.display();
    }
}

void Window::displayArtistsByGenre(sf::RenderWindow& window, HashMap& hashMap, sf::Font& font, int width, int height, const string& genre) {
    int yOffset = 50;
    for (const auto& genreItem : hashMap.getArtistsByGenre(genre)) {
        sf::Text genreText(genreItem, font, 40);
        genreText.setFillColor(sf::Color::White);
        setText(genreText, width / 2.0f, yOffset);
        window.draw(genreText);


        std::vector<Artist> artists = hashMap.getArtistsByGenre(genreItem);


        for (const auto& artistItem : artists) {
            sf::Text artistText(artistItem.getName(), font, 30);
            artistText.setFillColor(sf::Color::White);
            yOffset += 30;
            setText(artistText, width / 2.0f, yOffset);
            window.draw(artistText);
        }
        yOffset += 50;
    }
}

void Window::DisplayHashmap() {
    sf::RenderWindow hash;
    hash.create(sf::VideoMode(width, height), "Hash Map");

    sf::Text back("Return", font, 50);
    back.setFillColor(sf::Color::White);
    setText(back, width/10.0f, height/20.0f);

    while (hash.isOpen()) {
        sf::Event event;
        while (hash.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                hash.close();
            }
            if (event.type == sf::Event::TextEntered) {

            }
            if (event.type == sf::Event::KeyPressed) {

            }
            if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased) {
                if (back.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    hash.close();
                    DisplayWindow();
                }
            }
        }
        hash.clear(sf::Color::Transparent);
        displayArtistsByGenre(hash, hashMap, font, width, height, genre);
        hash.draw(back);
        hash.display();
    }
}

void setText(sf::Text text, float d, int offset) {

}

#endif //DSAPROJECT3_WINDOW_H