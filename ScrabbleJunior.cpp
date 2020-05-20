#include <iostream>
#include <vector>
#include <fstream>
#include "Board.h"
#include "Player.h"
#include "Pool.h"
#include <random>
#include <sstream>
#include <ctime>
#include <conio.h>
#include <map>

#define ROOT_PATH "C:\\Users\\joaof\\OneDrive\\Ambiente de Trabalho\\"
#define MAX_HAND_SIZE 7

using namespace std;

/* README
 * Nota que:
 * as duas jogadas, se possíveis, são iguais conceptualmente, portanto basta 1 função para as duas;
 * os pontos estão guardados no Player e portanto não precisas de uma estrutura separada;
 * a tua função winner não funciona para casos como, por exemplo, p0 > (p1 == p2 == p3) e pode ser bem simplificada
   para não ser uma cadeia de if-else's, aproveitando, talvez, o facto de os jogadores estarem organizados num vetor;
 * o vetor playStatus mostra o estado atual de cada peça do tabuleiro, permitindo uma fácil implementação das jogadas;
 * há umas propriedades muito interessantes sobre como é que o vetor se vai atualizando e como é que sabemos quando somar pontos.
   se conseguires dominá-las torna-se muito simples usar e manipulá-lo.
 * a pool estar vazia não é condição suficiente para despertar o fim do jogo. o melhor é ver se as mãos dos jogadores estão todas vazias
   ou se todos os espaços de letras estão preenchidos.
 */

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

Board parseBoardFile(const string &path, unsigned &size, vector<char> &tiles){
    ifstream fin;
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

vector<vector<short>> initialPlayStatus(const Board &board){
    unsigned size = board.getSize();
    vector<vector<short>> playStatus(0,vector<short>(0)); //initialize to all zeroes
    for(int x = 0; x < size; x++){
        for(int y = 0; y < size; y++){
            if (!board.getLetter(x-1,y) && !board.getLetter(x,y-1))
                playStatus[x][y] = 1;
        }
    }
}

bool playRound(Board &board, Player &player, Pool &pool, vector<vector<short>> &playStatus){
    static bool firstPlay = true;

    firstPlay = false;
}

void playGame(Board &board, vector<Player> &players, Pool &pool, vector<vector<short>> &playStatus){
    int currPlayer = 0;
    bool ended = false;
    while(!ended){
        ended = playRound(board, players[currPlayer], pool, playStatus);
        currPlayer = (currPlayer + 1) % players.size();
    }
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
    for (Player &player : players) {
        for (int j = 0; j < MAX_HAND_SIZE; j++)
            player.drawTile(pool);
    }
    //game itself
    playGame(board, players, pool, playStatus);
}
