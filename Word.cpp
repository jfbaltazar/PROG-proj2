//
// Created by joaof on 28/04/2020.
//

#include "Word.h"

string Word::getWord() const {
    return this->word;
}
void Word::setWord(const string &word){
    this->word = word;
}
string Word::getPosition() const {
    return this->pos;
}
void Word::setPosition(const string &coord){
    this->pos = coord;
}
char Word::getDirection() const {
    return this->dir;
}
void Word::setDirection(char dir){
    this->dir = dir;
}

