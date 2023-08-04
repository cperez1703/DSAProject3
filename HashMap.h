//
// Created by Scao0 on 8/3/2023.
//

#ifndef DSAPROJECT3_HASHMAP_H
#define DSAPROJECT3_HASHMAP_H

#endif //DSAPROJECT3_HASHMAP_H
#include <iostream>
#include <fstream>
#include <string>
#include "Artist.h"
#include <unordered_map>
#include <vector>
using namespace std;

class HashMap {
private:
    unordered_map<string, vector<Artist>> hashMap;
public:
    HashMap();
    int hashFunction(string genre);
};

HashMap::HashMap() {

}

int HashMap::hashFunction(string genre) {
    int hashedValue = 0;
    for (char i: genre) {
        hashedValue += int(i);
    }
    return hashedValue;
}
