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
#include <Windows.h>
#include <map>
#include <conio.h>

#define ROOT_PATH "C:\\Users\\joaof\\OneDrive\\Ambiente de Trabalho\\"
#define MAX_HAND_SIZE 7

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

//pronta
int getNumPlayers()
{
    int numPlayers;
    cout << "How many players (2 to 4) will play the game?";
    while (!getInput(numPlayers) || numPlayers < 2 || numPlayers >= 5)
        cout << endl << "Invalid number of players, try again (2 to 4).";
    return numPlayers;
}

//pronta
string getFileName()
{
    string fileName;
    cout << "What's the board's file name? ";
    cin >> fileName;
    return fileName;
}

//pronta
void convertCoordinates(const string& coord, int& x, int& y) {
    y = coord[0] - 'A';
    x = coord[1] - 'a';
}

//pronta
Board parseBoardFile(const string& path, vector<char>& tiles) {
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
    while (getline(fin, currentLine) && !currentLine.empty()) {
        istringstream(currentLine) >> coord >> direction >> word;
        convertCoordinates(coord, x, y);
        for (int i = 0; i < word.size(); i++) {
            if (direction == 'V')
                board.setLetter(x, y + i, word[i]);
            else
                board.setLetter(x + i, y, word[i]);
            tiles.push_back(word[i]);
        }
    }
    fin.close();
    return board;
}

vector<vector<short>> initialPlayStatus(const Board& board) {
    unsigned size = board.getSize();
    vector<vector<short>> playStatus(0, vector<short>(0)); //initialize to all zeroes
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            if (!board.getLetter(x - 1, y) && !board.getLetter(x, y - 1))
                playStatus[x][y] = 1;
        }
    }
}

bool playRound(Board& board, Player& player, Pool& pool, vector<vector<short>>& playStatus) {
    static bool firstPlay = true;

    //vou colocar aqui aquilo que penso que pediste
    int firsthouse;
    char doTrade, trade;
    int secondhouse;
    char tile1, tile2;
    int winner[4];
    cout << "If you can't play any tile enter 'Z'.\nInsert the house you'll put your first letter (i.e Ca): \n";
    cin >> firsthouse;
    while (!getInput(firsthouse) || firsthouse != 'Z' || firsthouse != 'y')
        cout << "That house doesn't exist.\nInsert the house you'll put your first letter (i.e Ca): ";

    if (firsthouse == 'Z' || firsthouse == 'z')
    {
        char trade1, trade2;
        char wantTrade;
        cout << "Do you want to trade 2 of your tiles? (yes or no) ";
        cin >> wantTrade;
        wantTrade = toupper(wantTrade);
        if (wantTrade == 'YES')
        {
            cout << "Which tiles do you want to trade? ";
            cin >> trade1; cin >> trade2;
            Player drawTile(Pool & pool);
            Player drawTile(Pool & pool);      
            pool.addTile(trade1);            
            pool.addTile(trade2);
        }
    }

    cout << "Play the tile for the house " << firsthouse << " you choose: ";
    cin >> tile1;
    tile1 = toupper(tile1);
    pool.extractTile();
    pool.addTile(tile1);
    cout << "Play the tile for the house " << secondhouse << " you choose.\n";
    cin >> tile2;
    tile2 = toupper(tile2);
    char extractTile(tile2);
    void addTile(char tile);

    cout << "If you don't want to play any tile press 'Y'.Insert the second house: ";
    while (!getInput(secondhouse) || secondhouse != 'Z' || secondhouse != 'y')
        cout << "That house doesn't exist.\nInsert the second house: ";
    if (secondhouse == 'Y' || secondhouse == 'y')
    {
        cout << "Do you want to trade 1 of your tiles? (yes or no) ";
        cin >> doTrade;
        doTrade = toupper(doTrade);
        if (doTrade == 'YES')
        {
            cout << "Which tile do you want to trade? ";
            cin >> trade;
            trade = toupper(trade);
            pool.addTile(trade);            //adicionar tile que não quer à pool
            player.drawTile(pool);
        }
    }



    //NãO SEI
    winner.getScore();

    //termina aqui

    firstPlay = false;
}

void playGame(Board& board, vector<Player>& players, Pool& pool, vector<vector<short>>& playStatus) {
    int currPlayer = 0;
    bool ended = false;
    while (!ended) {
        ended = playRound(board, players[currPlayer], pool, playStatus);
        currPlayer = (currPlayer + 1) % players.size();
    }
}


int main()
{
    srand(time(nullptr));
    unsigned size;
    vector<Player> players(getNumPlayers());
    vector<char> tiles;
    string filePath = ROOT_PATH;
    filePath += getFileName();
    if (tiles.size() / MAX_HAND_SIZE < players.size()) {
        cout << "The pool doesn't have enough tiles for this many players. Shutting down." << endl << "Press any key to close.";
        getch();
        return 1;
    }
    //initializing the game structures
    Board board = parseBoardFile(filePath, tiles);
    vector<vector<short>> playStatus = initialPlayStatus(board); //2 if coordinate played; 1 if coordinate playable; else 0
    Pool pool(tiles);
    for (Player& player : players) {
        for (int j = 0; j < MAX_HAND_SIZE; j++)
            player.drawTile(pool);
    }
    //game itself
    playGame(board, players, pool, playStatus);
    if (playStatus == 2)
    {
        cout << "That house already has a tile on it.\nTry another one.\n";
    }
    else if (playStatus == 1)
    {
        playRound(board, player, pool, playStatus);
    }
    else
    {
        cout << "Not possible to execute.\nTry again!\n";
    }
}
