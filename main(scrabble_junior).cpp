#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Board.h"
#include "Player.h"
#include "Pool.h"
#include <algorithm>
#include <random>
#include <sstream>
#include <ctime>

#define ROOT_PATH "C:\\Users\\joaof\\OneDrive\\Ambiente de Trabalho\\"
#define MAX_HAND_SIZE 7

using namespace std;

template <class T>
bool getInput(T &var) {
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
    cout << "How many players (2 to 4) will play the game?";
    while (!getInput(numPlayers) || numPlayers < 2 || numPlayers >= 5)
        cout << endl << "Invalid number of players, try again (2 to 4).";
    return numPlayers;
}

string getFileName()
{
    string fileName;
    cout << "What's the board's file name? ";
    cin >> fileName;
    return fileName;
}

void convertCoordinates(const string &coord, int &x, int &y) {
    y = coord[0] - 'A';
    x = coord[1] - 'a';
}

Board parseBoardFile(const string &path, vector<char> &tiles){
    ifstream fin;
    unsigned size;
    string currentLine;
    string coord;
    int x, y;
    char direction;
    string word;
    fin.open(path);
    fin >> size;
    Board board(size);
    while(getline(fin, currentLine) && !currentLine.empty()){
        istringstream(currentLine) >> coord >> direction >> word;
        convertCoordinates(coord, x, y);
        for (int i = 0; i < word.size(); i++) {
            if (direction == 'V')
                board.setLetter(x, y+i, word[i]);
            else
                board.setLetter(x+i, y, word[i]);
            tiles.push_back(word[i]);
        }
    }
    fin.close();
    return board;
}

//não está feita ainda
void distTiles()
{

}

char firstHouse()
{
    int firsthouse;
    cout << "Insert the house you'll put your first letter (i.e Ca): ";
    while (!getInput(firstHouse))
        cout << "That house doesn't exist.\nInsert the house you'll put your first letter (i.e Ca): ";
    return firsthouse;
}

char put1stTile(char firsthouse)
{
    char tile1, z;
    cout << "Play the tile for the house " << firsthouse << " you choose.\nIf you can't play any tile enter 'Z'.";
    cin >> tile1;
    z = toupper(tile1);
    //if (tile1 == 'Z')
    //    //tirar tiles atuais e colocar novas de forma aleatória
    //else
    //    continue;
    return tile1;
}

char secondHouse()
{
    int secondhouse;
    cout << "Insert the second house: ";
    while(!getInput(secondhouse))
        cout << "That house doesn't exist.\nInsert the second house: ";
    return secondhouse;
}

char put2ndTile(char secondhouse)
{
    char tile2, z;
    cout << "Play the tile for the house " << secondhouse << " you choose.\nIf you can't play any tile enter 'Z'.";
    cin >> tile2;
    z = toupper(tile2);
    //if (tile1 == 'Z')
    //    //tirar tiles atuais e colocar novas de forma aleatória
    //else
    //    continue;
    return tile2;
}

//não está feita
int points(char tile1, char tile2)
{

}

//falta loop que diz que a pool está vazia, fora da cadeia de if's
void winner(int score[4])
{
    if (score[0] > score[1] > score[2] > score[3])
        cout << "The winner is the Player 1 with " << score[0] << " points.";
    else if (score[1] > score[0] > score[2] > score[3])
        cout << "The winner is the Player 2 with " << score[1] << " points.";
    else if (score[2] > score[0] > score[1] > score[3])
        cout << "The winner is the Player 3 with " << score[2] << " points.";
    else if (score[3] > score[2] > score[1] > score[0])
        cout << "The winner is the Player 4 with " << score[3] << " points.";
}

int main()
{
    srand(time(nullptr));
    vector<Player> players(getNumPlayers());
    vector<char> tiles;
    string filePath = ROOT_PATH;
    filePath += getFileName();
    Board board = parseBoardFile(filePath, tiles);
    Pool pool(tiles);
    for (Player player : players) {
        for (int j = 0; j < MAX_HAND_SIZE; j++)
            player.drawTile(pool);
    }
    //jogo em si 
    return 0;
}