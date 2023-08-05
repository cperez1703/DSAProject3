//
// Created by Allie Montiague on 8/5/23.
//
#include "Artist.h"

Artist::Artist(string familiar, string name, string genre, string songId, string year)
        : familiar(familiar), name(name), genre(genre), songId(songId), year(year) {
}

const string& Artist::getGenre() const {
    return genre;

}

const string& Artist::getName() const {
    return name;
}


