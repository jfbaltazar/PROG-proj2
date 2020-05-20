#include <iostream>
#include "Board.h"
#include <fstream>
#include <algorithm>
#include <conio.h> //used for getch()

#define ROOT_PATH "C:\\Users\\joaof\\OneDrive\\Ambiente de Trabalho\\"
#define MIN_BOARD_SIZE 5
#define MAX_BOARD_SIZE 20

using namespace std;

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
    while (!getInput(size) || size < MIN_BOARD_SIZE || size > MAX_BOARD_SIZE){
        cout << endl << "Invalid size, please select a board size between " << MIN_BOARD_SIZE << " and " << MAX_BOARD_SIZE << ".";
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
    string currentWord;
    string path = ROOT_PATH;
    path += "WORDS.txt";
    bool result = false;
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    fin.open(path);
    while(getline(fin, currentWord)){
        if(currentWord == word) {
            result = true;
            break;
        }
    }
    fin.close();
    return result;
}

void convertCoordinates(const string &coord, int &x, int &y) {
    y = coord[0] - 'A';
    x = coord[1] - 'a';
}

bool outOfBounds(Board &board, const string &word, int x, int y, const char &direction){
    if(direction == 'V')
        y += word.size() - 1;
    else
        x += word.size() - 1;
    return !board.validPos(x,y);
}

bool addWord(Board &board, const string &word, int x, int y, char const &direction){
    if(direction == 'V'){
        if ( board.getLetter(x, y-1) || board.getLetter(x, y+word.size()) ) //verify head and tail of V word for unwanted letters
            return false;
        for(int i = 0; i < word.size(); i++) { //verify body
            if (board.getLetter(x, y+i)){ //is there a letter here?
                if (board.getLetter(x, y+i) != word[i]) //if so, it should be the same as the one to be inserted.
                    return false;
            } else
                if ( board.getLetter(x-1, y+i) || board.getLetter(x+1, y+i) ) //if not, no other letters should be around.
                    return false;
        }
        for(int i = 0; i < word.size(); i++) { //write to board
            board.setLetter(x, y+i, word[i]);
        }
    }
    else {
        if ( board.getLetter(x-1, y) || board.getLetter(x+word.size(), y) ) //verify head and tail of H word for unwanted letters
            return false;
        for(int i = 0; i < word.size(); i++) { //verify body
            if (board.getLetter(x+i, y)){ //is there a letter here?
                if (board.getLetter(x+i, y) != word[i]) //if so, it should be the same as the one to be inserted.
                    return false;
            }
            else if ( board.getLetter(x+i, y-1) || board.getLetter(x+i, y+1) ) //if not, no other letters should be around.
                return false;
        }
        for(int i = 0; i < word.size(); i++) { //write to board
            board.setLetter(x+i, y, word[i]);
        }
    }
    return true; //if successful write, this will be reached.
}

void manageNewWord(Board &board, vector<string> &vWords, vector<string> &hWords, vector<string> &vCoords, vector<string> &hCoords){
    string word;
    string start;
    int x,y;
    char direction = 0;
    bool success;
    cout << "Word?";
    getInput(word);
    transform(word.begin(), word.end(), word.begin(), ::toupper); //word is now fully uppercase.
    if(word.size() < 2 || !validWord(word)) { //is the word ok? (no 1-letter-words.)
        cout << "This word is either too short (min. 2 letters) or not in the dictionary." << endl;
        return;
    }
    cout << "Start?";
    getInput(start);
    convertCoordinates(start, x, y);
    if(start.size() != 2 || !board.validPos(x,y)){ //is the start legal?
        cout << "The start you chose is invalid." << endl;
        return;
    }
    cout << "Direction? (V/H)";
    getInput(direction);
    if ((direction != 'V' && direction != 'H') || outOfBounds(board, word, x, y, direction)){ //is the direction ok?
        cout << "The direction you chose is invalid or would lead to an illegal board state." << endl;
        return;
    }
    //word insertion attempt
    success = addWord(board, word, x, y, direction);
    if(success){
        if (direction == 'V') {
            vWords.push_back(word);
            vCoords.push_back(start);
        }
        else {
            hWords.push_back(word);
            hCoords.push_back(start);
        }
    }
    else
        cout << "I'm sorry, the word cannot fit here." << endl;
}

void saveContent(const Board &board, const vector<string> &vWords, const vector<string> &hWords, const vector<string> &vCoords, const vector<string> &hCoords){
    ofstream fout;
    unsigned size = board.getSize();
    string path = ROOT_PATH;
    path += "BOARD.txt";
    fout.open(path);
    fout << size << " x " << size << endl;
    for(int i = 0; i < hWords.size(); i++)
        fout << hCoords[i] << " H " << hWords[i] << endl;
    for(int i = 0; i < vWords.size(); i++)
        fout << vCoords[i] << " V " << vWords[i] << endl;
    fout << endl;
    board.show(fout);
}

int main() {
    Board board(selectSize()); //initialize with size
    vector<string> vWords, hWords;
    vector<string> vCoords, hCoords;
    char addingWords;
    do {
        cleanConsole();
        board.show(cout);
        manageNewWord(board, vWords, hWords, vCoords, hCoords);
        board.show(cout);
        cout << "Enter 'Y' if you want to continue.";
    } while(getInput(addingWords) && addingWords == 'Y');
    cleanConsole();
    cout << "Thank you, saving content now." << endl << endl;
    saveContent(board, vWords, hWords, vCoords, hCoords);
    cout << "Save complete. Press any key to close the program.";
    getch();
}