#pragma once

#include <string>
#include <vector>
using namespace std;

class Board {
private:
    vector<vector<char>> board;
    unsigned size;
public:
    const char letters[20] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't'};
    explicit Board(unsigned size);
    char getLetter(const int &x, const int &y) const;
    void setLetter(const int &x, const int &y, char letter);
    unsigned getSize() const;
    bool validPos(const int &x, const int &y) const;
    void show(ostream &out) const;
};

