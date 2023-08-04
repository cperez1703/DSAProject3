//
// Created by Calvi on 8/3/2023.
//

#ifndef DSAPROJECT3_ARTIST_H
#define DSAPROJECT3_ARTIST_H

#endif //DSAPROJECT3_ARTIST_H
class Artist{
private:
    string familiar;
    string genre;
    string name;
public:
    Artist(string familiar, string name, string genre);
};

Artist::Artist(string familiar, string name, string genre) {
    this->familiar = familiar;
    this->name = name;
    this->genre = genre;
}

