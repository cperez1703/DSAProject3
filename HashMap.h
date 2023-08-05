#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Artist.h"
#pragma once


class HashMap {
private:
    std::vector<std::vector<Artist>> hashTable;

public:
    HashMap();
    int hashFunction(std::string genre);
    void insert(const Artist& artist);
    std::vector<Artist> getArtistsByGenre(std::string genre);
};
HashMap::HashMap() {

    hashTable = std::vector<std::vector<Artist>>();
}


int HashMap::hashFunction(std::string genre) {
    int hashedValue = 0;
    for (char i : genre) {
        hashedValue += int(i);
    }
    return hashedValue;
}

void HashMap::insert(const Artist& artist) {
    int index = hashFunction(artist.getGenre());


    if (index >= hashTable.size()) {
        hashTable.resize(index + 1);
    }

    hashTable[index].push_back(artist);
}

std::vector<Artist> HashMap::getArtistsByGenre(std::string genre) {
    int index = hashFunction(genre);


    if (index >= hashTable.size()) {
        return std::vector<Artist>();
    }

    return hashTable[index];
}