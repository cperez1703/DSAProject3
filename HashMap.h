#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include "Artist.h"
#pragma once

class HashMap {
private:
    std::vector<std::vector<std::vector<Artist>>> hashTable;
    int tableSize = 0;

public:
    HashMap(int tableSize);
    int hashFunction(std::string genre);
    void insert(Artist artist);
    std::vector<Artist> getArtistsByGenre(std::string genre);
};
HashMap::HashMap(int size) : tableSize(size) {
    hashTable.resize(tableSize);
}

int HashMap::hashFunction(std::string genre) {//hash function based on ASCII values of string
    int hashedValue = 0;
    for (char i : genre) {
        hashedValue += int(i);
    }
    return hashedValue % tableSize;
}

void HashMap::insert(Artist artist) { //inserts artist object into hashmap
    int index = hashFunction(artist.genre);
    for(int i = 0; i < hashTable[index].size(); i++){
        if(hashTable[index][i].front().genre == artist.genre){
            hashTable[index][i].push_back(artist);
            return;
        }
    }
    hashTable[index].push_back({artist});
}

std::vector<Artist> HashMap::getArtistsByGenre(std::string genre) { //finds the artists with searched genre
    int index = hashFunction(genre);
    std::vector<Artist> matchingArtists;
    for (int i = 0; i < hashTable[index].size(); i++) {
        if (hashTable[index][i].front().genre == genre) {
            for(int j = 0; j < hashTable[index][i].size(); j++)
            matchingArtists.push_back(hashTable[index][i][j]);
        }
    }
    return matchingArtists;
}