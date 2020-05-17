#pragma once

#include <string>
#include <vector>

class Board {
public:
    explicit Board(unsigned size);
    char getLetter(const int &x, const int &y) const;
    void setLetter(const int &x, const int &y, char letter);
    unsigned getSize() const;
    bool validPos(const int &x, const int &y) const;
    void show(std::ostream &out) const;
private:
    std::vector<std::vector<char>> board;
    unsigned size;
};