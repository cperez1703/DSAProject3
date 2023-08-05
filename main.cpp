#include <iostream>
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Database.h"
#include "RedBlackTree.h"
#include "HashMap.h"

int main() {
    Database data("music.csv");
    Window w(1800,1000,"Welcome");
    w.DisplayWindow();
    return 0;
}
