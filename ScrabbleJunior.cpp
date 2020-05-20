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

bool playRound(Board& board, Player& player, Pool& pool, vector<vector<short>>& playStatus, char firsthouse, char secondhouse) {
    static bool firstPlay = true;
    //vou colocar aqui aquilo que penso que pediste
    char tile1, tile2;
    cout << "Play the tile for the house " << firsthouse << " you choose: ";
    cin >> tile1;
    tile1 = toupper(tile1);
    char extractTile(tile1);
    void addTile(char tile);
    //mudar cor da tile colocada no board
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 63); //assim muda também a cor do fundo, no caso penso que até fica melhor, perguntar ao João o que acha
    //pôr tile
    SetConsoleTextAttribute(hConsole, 15);
    
    char tile2;
    cout << "Play the tile for the house " << secondhouse << " you choose.\n";
    cin >> tile2;
    tile2 = toupper(tile2);
    char extractTile(tile2);
    void addTile(char tile);
    //mudar cor da nova tile
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 63);
    //pôr tile
    SetConsoleTextAttribute(hConsole, 15);
    //termina aqui

    firstPlay = false;
}

void playGame(Board& board, vector<Player>& players, Pool& pool, vector<vector<short>>& playStatus) {
    int currPlayer = 0;
    bool ended = false;
    while (!ended) {
        ended = playRound(board, players[currPlayer], pool, playStatus, firsthouse, secondhouse);
        currPlayer = (currPlayer + 1) % players.size();
    }
}

//está a dar 1 erro
char firstHouse(vector<char>& tiles)
{
    int firsthouse;
    cout << "If you can't play any tile enter 'Z'.\nInsert the house you'll put your first letter (i.e Ca): \n";
    cin >> firsthouse;
    while (!getInput(firstHouse) || firsthouse != 'Z' || firsthouse != 'y')
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
            Pool addTile(trade1);            //adicionar as tiles que não quer à pool está a dar um erro 
            Pool addTile(trade2);
            random_shuffle(tiles.begin(), tiles.end());
            Player drawTile(Pool & pool);
            Player drawTile(Pool & pool);//adiciona 2 tiles ao jogador (?)
        }

    }

    return firsthouse;
   
}

//está a dar 1 erro
char secondHouse(vector<char> tiles)
{
    char doTrade, trade;
    int secondhouse;
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
            Pool addTile(trade);            //adicionar tile que não quer à pool
            random_shuffle(tiles.begin(), tiles.end());
            Player drawTile(Pool& pool);
        }
    }
    
    return secondhouse;
}


//está a dar um erro ao usar a função endGame da classe Player
void winner(int score[4], vector<Player> players[4])
{
    if (Player endGame())
    {
        int maximum = max(score[0], max(score[1], max(score[2], score[3])));
        cout << "The winner have " << maximum << " points.\nCongradulations!";
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
    Board board = parseBoardFile(filePath, size, tiles);
    vector<vector<short>> playStatus = initialPlayStatus(board); //2 if coordinate played; 1 if coordinate playable; else 0
    Pool pool(tiles);
    for (Player& player : players) {
        for (int j = 0; j < MAX_HAND_SIZE; j++)
            player.drawTile(pool);
    }
    //game itself
    playGame(board, players, pool, playStatus);
    firstHouse(tiles);
    if (playStatus == 2)
    {
        cout << "That house already has a tile on it.\nTry another one.\n";
        firstHouse(tiles);
    }
    else if (playStatus == 1)
    {
        playRound( board, player, pool, playStatus, firsthouse, secondhouse);

    }
    else
    {
        cout << "Not possible to execute.\nTry again!\n";
        firstHouse(tiles);
    }
}
