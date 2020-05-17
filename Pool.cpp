//
// Created by joaof on 17/05/2020.
//

#include "Pool.h"
#include <random>


Pool::Pool(const std::vector<char> &letters) {
    for (char letter : letters) {
        this->tiles.push_back(letter);
    }
}

void Pool::addTile(char tile) {
    this->tiles.push_back(tile);
}

char Pool::extractTile() {
    unsigned index;
    if(this->tiles.empty())
        return 0;
    index = tiles[rand() % this->tiles.size()];
    this->tiles.erase(this->tiles.begin()+index);
    return this->tiles[index];
}


