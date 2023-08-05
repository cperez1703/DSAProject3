#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include "Artist.h"
#pragma once



class HashMap {
private:



    std::vector<std::list<Artist>> hashTable;
    //changed to a list so each bucket in hash table can
    int tableSize;

public:
    HashMap(int tableSize);
    int hashFunction(std::string genre);
    void insert(const Artist& artist);
    std::vector<Artist> getArtistsByGenre(std::string genre);
};
HashMap::HashMap(int size) : tableSize(size) {
    hashTable.resize(tableSize);
}


int HashMap::hashFunction(std::string genre) {
    int hashedValue = 0;
    for (char i : genre) {
        hashedValue += int(i);
    }
    return hashedValue % tableSize;
}

void HashMap::insert(const Artist& artist) {
    int index = hashFunction(artist.getGenre());

        while (!hashTable[index].empty()) {
        // Find next avail slot by incrementing index
            index++;
        // Wrap around to  beginning if reaches
        //  end of hash table
            if (index >= hashTable.size()) {
                index = 0;
        }
    }

    // Insert the artist into  found slot*/
    hashTable[index].push_back(artist);
}


std::vector<Artist> HashMap::getArtistsByGenre(std::string genre) {
    int index = hashFunction(genre);
    std::vector<Artist> matchingArtists;

    for (const auto& artist : hashTable[index]) {
        if (artist.getGenre() == genre) {
            matchingArtists.push_back(artist);
        }
    }

    return matchingArtists;
}