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
#pragma once
using namespace std;

class Database{
private:
    vector<Artist> artists;
public:
    Database(string file);
    vector<Artist> Artists();
};

Database::Database(string file) {//reads in the file and creates artist vector
    ifstream inFile;
    inFile.open(file);
    string line;

    string familiar;
    string name;
    string genre;
    string songId;
    string year;
    getline(inFile,line);
    while(getline(inFile, familiar,',')){
        getline(inFile, name, ',');
        getline(inFile, genre, ',');
        getline(inFile, songId, ',');
        getline(inFile, year);
        artists.push_back(Artist(familiar, name, genre, songId, year));
    }
    inFile.close();
}

vector<Artist> Database::Artists() {//returns vector of artist objects
    return artists;
}
