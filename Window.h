#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "RedBlackTree.h"
#include "HashMap.h"
#include <math.h>

using namespace std;

class Window {
private:
    sf::RenderWindow window;
    string name;
    int width;
    int height;
    sf::Font font;
    int page;
    vector<Artist> objects;
    vector<vector<sf::Text>> recommendedArtistsT;
    vector<vector<sf::Text>> recommendedFamiliarT;
    vector<vector<sf::Text>> recommendedSongIdT;
    vector<vector<sf::Text>> recommendedYearT;
    void setText(sf::Text &text, float x, float y, sf::Color color);
    void DisplayRedBlack();
    void DisplayHashmap();
    void CreateArtists(vector<vector<string>> recommendedArtists);
public:
    Window(int width, int height, string name,vector<Artist> objects);
    void DisplayWindow();
};

Window::Window(int width, int height, string name,vector<Artist> objects) { //constructor for welcome window
    this->name = name;
    this->width = width;
    this->height = height;
    this->page = -1;
    font.loadFromFile("OpenSans-Regular.ttf");
    this->objects = objects;
}

void Window::setText(sf::Text &text, float x, float y, sf::Color color) { //sets the text at centered desired location and color
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
    text.setFillColor(color);
}

void Window::DisplayWindow() { //displays the welcome window
    window.create(sf::VideoMode(width, height), name);
    //creation of text
    sf::Text titleT("Undercover Artists", font, 100);
    titleT.setOutlineColor(sf::Color::White);
    titleT.setOutlineThickness(3);
    setText(titleT, width/2.0f, height/3.0f, sf::Color::Black);
    sf::Text redBlackT("Red-Black Tree", font, 50);
    setText(redBlackT, width/2.0f, height/2.0f, sf::Color::White);
    sf::Text hashmapT("Hash Map", font, 50);
    setText(hashmapT, width/2.0f, height/3.0f*2,sf::Color::White);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased){
                if(redBlackT.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){//opens red-black window
                    window.close();
                    DisplayRedBlack();
                }
                if(hashmapT.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){//opens hashmap window
                    window.close();
                    DisplayHashmap();
                }
            }
        }
        window.clear(sf::Color::Transparent); // keep drawings below
        window.draw(titleT);
        window.draw(redBlackT);
        window.draw(hashmapT);
        window.display();// keep drawings above
    }
}

void Window::DisplayRedBlack() {//displays redblack window
    sf::RenderWindow redBlack;
    redBlack.create(sf::VideoMode(width, height), "Red-Black");
    //creation of text
    sf::Text backT("Return", font, 50);
    setText(backT, width/10.0f, height/20.0f,sf::Color::White);
    sf::Text searchT("Search:", font, 50);
    setText(searchT, width/10.0f, height/10.0f,sf::Color::White);
    sf::Text timeT("Time: ", font, 50);
    setText(timeT, width/10.0f*5, height/20.0f,sf::Color::White);
    sf::Text userInputT("Search:", font, 50);
    setText(userInputT, width/10.0f + searchT.getLocalBounds().width + 5, height/10.0f, sf::Color::White);
    userInputT.setString("");
    sf::Text artistT("Artists", font, 50);
    artistT.setStyle(sf::Text::Underlined);
    setText(artistT,width/15.0f, height/5.0f, sf::Color::White);
    sf::Text familiarT("Null", font, 50);
    familiarT.setStyle(sf::Text::Underlined);
    setText(familiarT, width/15.0f*5.2, height/5.0f, sf::Color::White);
    familiarT.setString("Familiarity");
    sf::Text songIdT("Null", font, 50);
    songIdT.setStyle(sf::Text::Underlined);
    setText(songIdT, width/15.0f*9, height/5.0f, sf::Color::White);
    songIdT.setString("Song Id");
    sf::Text yearT("Year", font, 50);
    yearT.setStyle(sf::Text::Underlined);
    setText(yearT, width/15.0f*13, height/5.0f, sf::Color::White);
    sf::Text leftT("<", font, 50);
    setText(leftT,width/10.0f*5, height/10.0f, sf::Color::White);
    sf::Text rightT(">", font, 50);
    setText(rightT,width/10.0f*6, height/10.0f, sf::Color::White);
    sf::Text pageT("Page: ", font, 50);
    setText(pageT, width/10.0f*8, height/10.0f, sf::Color::White);
    string input = "";

    while(redBlack.isOpen())
    {
        sf::Event event;
        while (redBlack.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                redBlack.close();
            }
            //creates the text for user input
            if (event.type == sf::Event::TextEntered && (isalpha(event.text.unicode) || event.text.unicode == 32 || event.text.unicode == 45)){
                if(input.length() < 20){
                    input += event.text.unicode;
                    userInputT.setString(input);
                }
            }
            if (event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Backspace && input.length() > 0){
                    input.pop_back();
                    userInputT.setString(input);
                }
                //once enter is pressed it creates the artist text
                if(event.key.code == sf::Keyboard::Enter && input.length() > 0){
                    page = 0;
                    pageT.setString("Page: " + to_string(page+1));
                    recommendedArtistsT.clear();
                    recommendedFamiliarT.clear();
                    recommendedSongIdT.clear();
                    recommendedYearT.clear();
                    sf::Clock clock;
                    ////do red black search
                    RedBlackTree tree(objects);
                    vector<Artist> result = tree.searchGenre(input);
                    vector<string> artists;
                    vector<string> familiars;
                    vector<string> songs;
                    vector<string> year;
                    for(int i = 0; i < result.size(); i++){
                        if(result[i].name.length() > 22){
                            artists.push_back(result[i].name.substr(0,19) + "...");
                        }else{
                            artists.push_back(result[i].name);
                        }
                        familiars.push_back(to_string(stod(result[i].familiar)));
                        songs.push_back(result[i].songId);
                        year.push_back(result[i].year);
                    }
                    vector<vector<string>> textT;
                    textT.push_back(artists);
                    textT.push_back(familiars);
                    textT.push_back(songs);
                    textT.push_back(year);
                    ////
                    sf::Time t = clock.getElapsedTime();
                    string time = to_string(t.asMilliseconds());
                    timeT.setString("Time: " + time + "ms");
                    CreateArtists(textT);
                }
            }
            if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased){
                //returns to welcome window
                if(backT.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
                    page = -1;
                    recommendedArtistsT.clear();
                    recommendedFamiliarT.clear();
                    recommendedSongIdT.clear();
                    recommendedYearT.clear();
                    redBlack.close();
                    DisplayWindow();
                }
                //changes page
                if(leftT.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
                    if(page>0){
                        page-=1;
                        pageT.setString("Page: " + to_string(page+1));
                    }
                }
                if(rightT.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
                    if(page<recommendedArtistsT.size()-1){
                        page+=1;
                        pageT.setString("Page: " + to_string(page+1));
                    }
                }
            }
        }
        redBlack.clear(sf::Color::Transparent); // keep drawings below
        redBlack.draw(backT);
        redBlack.draw(searchT);
        redBlack.draw(userInputT);
        redBlack.draw(timeT);
        redBlack.draw(timeT);
        redBlack.draw(artistT);
        redBlack.draw(leftT);
        redBlack.draw(rightT);
        redBlack.draw(pageT);
        redBlack.draw(familiarT);
        redBlack.draw(songIdT);
        redBlack.draw(yearT);
        if(page > -1){
            for(int i = 0; i < recommendedArtistsT.at(page).size(); i++){
                redBlack.draw(recommendedArtistsT[page][i]);
                redBlack.draw(recommendedFamiliarT[page][i]);
                redBlack.draw(recommendedSongIdT[page][i]);
                redBlack.draw(recommendedYearT[page][i]);
            }
        }
        redBlack.display();// keep drawings above
    }
}

void Window::DisplayHashmap() {
    sf::RenderWindow hash;
    hash.create(sf::VideoMode(width, height), "Hash Map");
    //creation of text
    sf::Text backT("Return", font, 50);
    setText(backT, width/10.0f, height/20.0f,sf::Color::White);
    sf::Text searchT("Search:", font, 50);
    setText(searchT, width/10.0f, height/10.0f,sf::Color::White);
    sf::Text timeT("Time: ", font, 50);
    setText(timeT, width/10.0f*5, height/20.0f,sf::Color::White);
    sf::Text userInputT("Search:", font, 50);
    setText(userInputT, width/10.0f + searchT.getLocalBounds().width + 5, height/10.0f, sf::Color::White);
    userInputT.setString("");
    sf::Text artistT("Artists", font, 50);
    artistT.setStyle(sf::Text::Underlined);
    setText(artistT,width/15.0f, height/5.0f, sf::Color::White);
    sf::Text familiarT("Null", font, 50);
    familiarT.setStyle(sf::Text::Underlined);
    setText(familiarT, width/15.0f*5.2, height/5.0f, sf::Color::White);
    familiarT.setString("Familiarity");
    sf::Text songIdT("Null", font, 50);
    songIdT.setStyle(sf::Text::Underlined);
    setText(songIdT, width/15.0f*9, height/5.0f, sf::Color::White);
    songIdT.setString("Song Id");
    sf::Text yearT("Year", font, 50);
    yearT.setStyle(sf::Text::Underlined);
    setText(yearT, width/15.0f*13, height/5.0f, sf::Color::White);
    sf::Text leftT("<", font, 50);
    setText(leftT,width/10.0f*5, height/10.0f, sf::Color::White);
    sf::Text rightT(">", font, 50);
    setText(rightT,width/10.0f*6, height/10.0f, sf::Color::White);
    sf::Text pageT("Page: ", font, 50);
    setText(pageT, width/10.0f*8, height/10.0f, sf::Color::White);
    string input = "";

    while(hash.isOpen())
    {
        sf::Event event;
        while (hash.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                hash.close();
            }
            //creates the text for user input
            if (event.type == sf::Event::TextEntered && (isalpha(event.text.unicode) || event.text.unicode == 32 || event.text.unicode == 45)){
                if(input.length() < 20){
                    input += event.text.unicode;
                    userInputT.setString(input);
                }
            }
            if (event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Backspace && input.length() > 0){
                    input.pop_back();
                    userInputT.setString(input);
                }
                //once enter is pressed it creates the artist text
                if(event.key.code == sf::Keyboard::Enter && input.length() > 0){
                    page = 0;
                    pageT.setString("Page: " + to_string(page+1));
                    recommendedArtistsT.clear();
                    recommendedFamiliarT.clear();
                    recommendedSongIdT.clear();
                    recommendedYearT.clear();
                    sf::Clock clock;
                    ////do hash map search
                    HashMap map(460);
                    for(int i = 0; i < objects.size(); i++){
                        map.insert(objects[i]);
                    }
                    vector<Artist> result = map.getArtistsByGenre(input);
                    vector<string> artists;
                    vector<string> familiars;
                    vector<string> songs;
                    vector<string> year;
                    for(int i = 0; i < result.size(); i++){
                        if(result[i].name.length() > 22){
                            artists.push_back(result[i].name.substr(0,19) + "...");
                        }else{
                            artists.push_back(result[i].name);
                        }
                        familiars.push_back(to_string(stod(result[i].familiar)));
                        songs.push_back(result[i].songId);
                        year.push_back(result[i].year);
                    }
                    vector<vector<string>> textT;
                    textT.push_back(artists);
                    textT.push_back(familiars);
                    textT.push_back(songs);
                    textT.push_back(year);
                    ////
                    sf::Time t = clock.getElapsedTime();
                    string time = to_string(t.asMilliseconds());
                    timeT.setString("Time: " + time + "ms");
                    CreateArtists(textT);
                }
            }
            if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased){
                //returns to welcome window
                if(backT.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
                    page = -1;
                    recommendedArtistsT.clear();
                    recommendedFamiliarT.clear();
                    recommendedSongIdT.clear();
                    recommendedYearT.clear();
                    hash.close();
                    DisplayWindow();
                }
                //changes page
                if(leftT.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
                    if(page>0){
                        page-=1;
                        pageT.setString("Page: " + to_string(page+1));
                    }
                }
                if(rightT.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
                    if(page<recommendedArtistsT.size()-1){
                        page+=1;
                        pageT.setString("Page: " + to_string(page+1));
                    }
                }
            }
        }
        hash.clear(sf::Color::Transparent); // keep drawings below
        hash.draw(backT);
        hash.draw(searchT);
        hash.draw(userInputT);
        hash.draw(timeT);
        hash.draw(timeT);
        hash.draw(artistT);
        hash.draw(familiarT);
        hash.draw(songIdT);
        hash.draw(yearT);
        hash.draw(leftT);
        hash.draw(rightT);
        hash.draw(pageT);
        if(page > -1){
            for(int i = 0; i < recommendedArtistsT.at(page).size(); i++){
                hash.draw(recommendedArtistsT[page][i]);
                hash.draw(recommendedFamiliarT[page][i]);
                hash.draw(recommendedSongIdT[page][i]);
                hash.draw(recommendedYearT[page][i]);
            }
        }
        hash.display();// keep drawings above
    }
}

void Window::CreateArtists(vector<vector<string>> recommendedArtists) { // creates the text for found artists
    vector<sf::Text> artistTexts;
    vector<sf::Text> familiarTexts;
    vector<sf::Text> songIdTexts;
    vector<sf::Text> yearTexts;
    for(int i = 0; i < recommendedArtists[0].size(); i++){
        sf::Text artistT(recommendedArtists[0][i], font, 50);
        artistT.setFillColor(sf::Color::White);
        artistT.setPosition(10, height/5.0f+(((i%15)+1)*50-25));
        artistTexts.push_back(artistT);

        sf::Text familiarT(recommendedArtists[1][i], font, 50);
        familiarT.setFillColor(sf::Color::White);
        familiarT.setPosition( width/15.0f*5.2, height/5.0f+(((i%15)+1)*50-25));
        familiarTexts.push_back(familiarT);

        sf::Text songT(recommendedArtists[2][i], font, 50);
        songT.setFillColor(sf::Color::White);
        songT.setPosition(width/15.0f*7.5, height/5.0f+(((i%15)+1)*50-25));
        songIdTexts.push_back(songT);

        sf::Text yearT(recommendedArtists[3][i], font, 50);
        yearT.setFillColor(sf::Color::White);
        yearT.setPosition(width/15.0f*12.5, height/5.0f+(((i%15)+1)*50-25));
        yearTexts.push_back(yearT);

        if((i+1)%15 == 0){
            recommendedArtistsT.push_back(artistTexts);
            recommendedFamiliarT.push_back(familiarTexts);
            recommendedSongIdT.push_back(songIdTexts);
            recommendedYearT.push_back(yearTexts);
            artistTexts.clear();
            familiarTexts.clear();
            songIdTexts.clear();
            yearTexts.clear();
        }
    }
    recommendedArtistsT.push_back(artistTexts);
    recommendedFamiliarT.push_back(familiarTexts);
    recommendedSongIdT.push_back(songIdTexts);
    recommendedYearT.push_back(yearTexts);
}
