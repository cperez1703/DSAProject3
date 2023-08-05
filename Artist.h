#ifndef DSAPROJECT3_ARTIST_H
#define DSAPROJECT3_ARTIST_H

#include <string>
using namespace std;

class Artist {
private:
    string familiar;
    string genre;
    string name;
    string songId;
    string year;

public:
    Artist(string familiar, string name, string genre, string songId, string year);

    const string& getGenre() const;
    const string& getName() const;
};

#endif // DSAPROJECT3_ARTIST_H



