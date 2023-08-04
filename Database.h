//
// Created by Calvi on 8/2/2023.
//

#ifndef DSAPROJECT3_DATABASE_H
#define DSAPROJECT3_DATABASE_H

#endif //DSAPROJECT3_DATABASE_H

#include <iostream>
#include <fstream>
#include <string>
#include "Artist.h"
using namespace std;

class Database{
private:
    vector<Artist> artists;
public:
    Database(string file);
    vector<Artist> Artists();
};

Database::Database(string file) {
    ifstream inFile;
    inFile.open(file);
    string line;

    string familiar;
    string name;
    string genre;
    while(getline(inFile, line)){
        getline(inFile, familiar, ',');
        for(int i = 0; i < 5; i++){
            getline(inFile, line, ',');
        }
        getline(inFile, name, ',');
        getline(inFile, line, ',');
        getline(inFile, genre, ',');
        for(int i = 0; i < 25; i++){
            getline(inFile, line, ',');
        }
        artists.push_back(Artist(familiar, name, genre));
    }
    artists.pop_back(); // deletes last element(not sure why but adds the last element twice)
    inFile.close();
}

vector<Artist> Database::Artists() {
    return artists;
}
