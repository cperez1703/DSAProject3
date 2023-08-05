//
// Created by Calvi on 8/3/2023.
//

#ifndef DSAPROJECT3_ARTIST_H
#define DSAPROJECT3_ARTIST_H

#endif //DSAPROJECT3_ARTIST_H
class Artist{ // creates artist objects
public:
    string familiar;
    string genre;
    string name;
    string songId;
    string year;
    Artist(string familiar, string name, string genre, string songId, string year);
};

Artist::Artist(string familiar, string name, string genre, string songId, string year) {
    this->familiar = familiar;
    this->name = name;
    this->genre = genre;
    this->songId = songId;
    this->year = year;
}

