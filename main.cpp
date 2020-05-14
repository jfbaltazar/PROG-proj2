#include <iostream>
#include "Board.h"
#include <fstream>
#include <algorithm>

#define ROOT_PATH "C:\\Users\\joaof\\OneDrive\\Ambiente de Trabalho\\"


template <class T>
bool getInput(T &var){
    T aux;
    if(cin >> aux && cin.peek() == '\n') {
        var = aux;
        return true;
    }
    else {
        cin.ignore(10000, '\n');
        cin.clear();
        return false;
    }
}

unsigned selectSize(){
    unsigned size;
    cout << "Size, please!";
    while (!getInput(size) || size < 5 || size > 20){
        cout << endl << "Invalid size, please select a board size between 5 and 20.";
    }
    cout << endl;
    return size;
}

void cleanConsole(){
    cout << flush;
    system("CLS");
}

bool validWord(string word){
    ifstream fin;
    string current;
    string path = ROOT_PATH;
    path += "WORDS.txt";
    bool result = false;
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    fin.open(path);
    while(getline(fin, current)){
        if(current.find(word) != string::npos)
            result = true;
    }
    fin.close();
    return result;
}

void convertCoordinates(const string &coord, int &x, int &y) {
    y = coord[0] - 'A';
    x = coord[1] - 'a';
}

bool outOfBounds(Board &board, string const &word, string const &start, char const &direction){
    int x1,y1;
    convertCoordinates(start, x1, y1);
    int x2 = x1, y2 = y1;
    if(direction == 'V') {
        x2 += word.size();
    }
    else {
        y2 += word.size();
    }
    return ( !board.validPos(x1,y1) || !board.validPos(x2,y2) );
}

bool addWord(Board &board, string word, int x, int y, char const &direction){
    transform(word.begin(), word.end(), word.begin(), ::toupper);
    if(direction == 'V'){
        if ( board.getLetter(x, y-1) || board.getLetter(x, y+word.size()+1) ) //verify head and tail of V word
            return false;
        for(int i = 0; i < word.size(); i++) { //verify body
            if (board.getLetter(x, y+i)){
                if (board.getLetter(x, y+i) != word[i])
                    return false;
            } else
                if ( board.getLetter(x-1, y+i) || board.getLetter(x+1, y+i) )
                    return false;
        }
        for(int i = 0; i < word.size(); i++) { //write to board
            board.setLetter(x, y+i, word[i]);
        }
    }
    else {
        if ( board.getLetter(x-1, y) || board.getLetter(x+word.size()+1, y) ) //verify head and tail of H word
            return false;
        for(int i = 0; i < word.size(); i++) { //verify body
            if (board.getLetter(x+i, y)){
                if (board.getLetter(x+i, y) != word[i])
                    return false;
            } else
            if ( board.getLetter(x+i, y-1) || board.getLetter(x+i, y+1) )
                return false;
        }
        for(int i = 0; i < word.size(); i++) { //write to board
            board.setLetter(x+i, y, word[i]);
        }
    }
    return true; //if successful write, this will be reached.
}

void manageWord(Board &board){
    string word;
    string start;
    int x,y;
    char direction = 0;
    bool success;
    cout << "Word?";
    getInput(word);
    if(word.size() < 2 || !validWord(word)) { //is the word ok? (no 1-letter-words.)
        cout << "This word is either too short (min. 2 letters) or not in the dictionary." << endl;
        return;
    }
    cout << "Start?";
    getInput(start);
    convertCoordinates(start, x, y);
    if(start.size() != 2 || !board.validPos(x, y)){ //is the start ok?
        cout << "The start you chose is invalid." << endl;
        return;
    }
    cout << "Direction? (V/H)";
    getInput(direction);
    if (direction != 'V' && direction != 'H') //is the direction ok?
        cout << "The direction you chose is invalid." << endl;
    //word insertion attempt
    success = addWord(board, word, x, y, direction);
    if(!success)
        cout << "I'm sorry, the word cannot fit here." << endl;
}

void saveContent(const Board &board){
    ofstream fout;
    unsigned size = board.getSize();
    string path;
    char last = 0;
    path += "BOARD.txt";
    fout.open(path);
    fout << size << " x " << size << endl;
    for (int x = 0; x < size; x++) {
        for(int j = 0; j < size; j++){
            fout << board.getLetter(x,j);
        }
    }
}

int main() {
    Board board(selectSize()); //initialize with size
    char addingWords;
    do {
        cleanConsole();
        manageWord(board);
        board.show(cout);
        cout << "Enter 'Y' if you want to continue.";
    } while(getInput(addingWords) && addingWords == 'Y');
    //ofstream fout;
    //saveContent();
}
