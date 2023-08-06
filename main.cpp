#include <iostream>
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Database.h"
#pragma once

int main() {
    Database data("music.csv");//reads in the data and stores in vector
    Window w(1800,1000,"Welcome",data.Artists());//creates window
    w.DisplayWindow();
    return 0;
}