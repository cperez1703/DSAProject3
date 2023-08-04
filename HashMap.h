#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class HashMap {
private:
    vector<string,vector<Artist>> hashTable;

public:
    HashMap();
    int hashFunction(string genre);
};

int HashMap::hashFunction(string genre) {
    int hashedValue = 0;
    for (char i: genre) {
        hashedValue += int(i);
    }
    return hashedValue;
}
