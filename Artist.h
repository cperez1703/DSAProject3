#pragma once
class Artist{ // creates artist objects
public:
    std::string familiar;
    std::string genre;
    std::string name;
    std::string songId;
    std::string year;
    Artist(std::string familiar, std::string name, std::string genre, std::string songId, std::string year);
};

Artist::Artist(std::string familiar, std::string name, std::string genre, std::string songId, std::string year) {
    this->familiar = familiar;
    this->name = name;
    this->genre = genre;
    this->songId = songId;
    this->year = year;
}

