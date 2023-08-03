#include <iostream>
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Database.h"
#include "RedBlackTree.h"

int main() {
    Window w(500,500,"Welcome");
    sf::Text welcome;
    welcome.setString("Sonny");
    w.DisplayWindow();
    return 0;
}
