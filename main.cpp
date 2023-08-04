#include <iostream>
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Database.h"
#include "RedBlackTree.h"
#include "HashMap.h"
#pragma once

int main() {
//    Database data("music.csv");
    Window w(1000,1000,"Welcome");
    w.DisplayWindow();
    return 0;
}
