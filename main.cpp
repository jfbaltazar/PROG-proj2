#include <iostream>
#include "Board.h"
#include "Word.h"
#include <fstream>
#include <random>

int main() {
    int size;
    Board board;
    string aux;
    ifstream fin;
    ofstream fout;
    cout << "Size?"; cin >> size;
    fin.open(R"(C:\Users\joaof\OneDrive\Ambiente de Trabalho\WORDS.txt)");
    //choose words and add them to board
    fin.close();
    fout.open("BOARD.txt");
    fout << size << " x " << size << endl;
    for(int i = 0; i < wordCount; i++){
        fout << word.getPosition() << " " << word.getWord() << " " << word.getDirection() << endl;
    }
    fout.close();
}
