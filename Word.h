//
// Created by joaof on 28/04/2020.
//

#pragma once

#include <string>
using namespace std;

class Word {
private:
    string word;
    string pos;
    char dir;
public:
    string getWord() const;
    void setWord(string &word);
    string getPosition() const;
    void setPosition(const string &coord);
    char getDirection() const;
    void setDirection(char dir);
};
