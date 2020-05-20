//
// Created by joaof on 17/05/2020.
//

#pragma once

#include <vector>

class Pool {
public:
    explicit Pool(const std::vector<char> &letters);
    void addTile(char tile);
    char extractTile();
    bool isEmpty() const;
private:
    std::vector<char> tiles;
};



