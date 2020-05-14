//
// Created by joaof on 21/04/2020.
//

#include "Board.h"
#include <iostream>

using namespace std;

Board::Board(unsigned size){
    this->size = size;
    this->board.resize(size, vector<char>(size, '\0'));
}

char Board::getLetter(const int &x, const int &y) const{
    if(!validPos(x,y))
        return '\0';
    return this->board[x][y];
}

void Board::setLetter(const int &x, const int &y, char letter) {
    this->board[x][y] = letter;
}

unsigned Board::getSize() const {
    return this->size;
}

bool Board::validPos(const int &x, const int &y) const {
    return (x >= 0) && (x <= this->size) && (y >= 0) && (y <= this->size);
}

void Board::show(ostream &out) const {
    out << " ";
    for(int i = 0; i < size; i++){
        out << " " << (char) i + 'a';
    }
    cout << endl;
    for(int y = 0; y < size; y++){
        out << (char) y + 'A';
        for(int x = 0; x < size; x++){
            out << " " << this->board[x][y];
        }
        out << endl;
    }
}