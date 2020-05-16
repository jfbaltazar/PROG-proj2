#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Board.h"
#include "Player.h"
#include "Pool.h"
#include <algorithm>
#include <random>
#define ROOT_PATH "Ambiente de Trabalho"
using namespace std;

template <class T>
bool getInput(T& var) {
    T aux;
    if (cin >> aux && cin.peek() == '\n') {
        var = aux;
        return true;
    }
    else {
        cin.ignore(10000, '\n');
        cin.clear();
        return false;
    }
}

int getNumPlayers()
{
    int numPlayers;
    cout << "How many players (2 to 4) will play the game? \n";
    while (!getInput(numPlayers) || numPlayers < 2 || numPlayers >= 5)
        cout << "Invalid number of players, try again (2 to 4).";
    return numPlayers;
}

string getFileName()
{
    string fileName;
    cout << "What's the board's file name? ";
    cin >> fileName;
    return fileName;
}



int main()
{

    int numPlayers = getNumPlayers();
    string fileName = ROOT_PATH;
    fileName += getFileName();
    vector<Player> players(numPlayers);
    //inicializar board
    //inicializar pool
    //distribuir tiles
    //jogo em si 
}
