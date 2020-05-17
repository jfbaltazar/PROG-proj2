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

//não está terminada
void saveBoard(const Board &board)
{
    int i;
    ofstream fout;
    unsigned size = board.getSize();
    string fileName = ROOT_PATH;
    fileName += "BOARD.txt";
    fout.open(fileName);
    /*for ()
    {

    }
    */
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


string getFileName();
int getNumPlayers();
void distFirstTiles(vector<char> pool, int& player, const int NumPlayers);
char firstHouse();
char put1stTile(char firsthouse);
char secondHouse();
char put2ndTile(char secondhouse);
void distTiles();
int points(char tile1, char tile2);
void show(ostream& out);
void saveBoard(const Board& board);
void winner(int score[4]);

int main()
{
    int score[4] = {0, 0, 0, 0};
    int numPlayers = getNumPlayers();
    string fileName = ROOT_PATH;
    fileName += getFileName();
    vector<Player> players(numPlayers);

    //swapPlayers
    /*if (numPlayers == 0)
        numPlayers = 1;
    else if (numPlayers == 1)
        numPlayers = 2;
    else if (numPlayers == 2)
        numPlayers = 3;
    else if (numPlayers == 3)
        numPlayers = 0;*/

    while (true)
    {
        getNumPlayers();
        getFileName();
        show(ostream & out);

        winner(int score[4]);
    }
    //inicializar board
    //inicializar pool
    //distribuir tiles
    //jogo em si 
    return 0;
}
