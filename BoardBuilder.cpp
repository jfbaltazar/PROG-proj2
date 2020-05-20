#include <iostream>
#include "Board.h"
#include <fstream>
#include <algorithm>
#include <conio.h> //used for getch()

#define ROOT_PATH ""      //the root path for WORDS.txt and BOARD.txt
#define MIN_BOARD_SIZE 5
#define MAX_BOARD_SIZE 20

using namespace std;

/**
 * If successful in receiving a value of type T from the user, write it to var.
 * @param var Any variable to be assigned a value through cin.
 * @return True if the assignment is successful.
 */
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

/**
 * Ask to console for a board size between MIN_BOARD_SIZE and MAX_BOARD_SIZE.
 * @return The chosen size.
 */
unsigned selectSize(){
    unsigned size;
    cout << "Size, please!";
    while (!getInput(size) || size < MIN_BOARD_SIZE || size > MAX_BOARD_SIZE){
        cout << endl << "Invalid size, please select a board size between " << MIN_BOARD_SIZE << " and " << MAX_BOARD_SIZE << ".";
    }
    cout << endl;
    return size;
}

/**
 * Visually clean the console screen.
 */
void cleanConsole(){
    cout << flush;
    system("cls");
}

/**
 * Given a word, determine if it is contained in the dictionary "WORDS.txt".
 * @param word The word to be searched up.
 * @return True if it is contained.
 */
bool validWord(string word){
    ifstream fin;
    string currentWord;
    string path = ROOT_PATH;
    path += "WORDS.txt";
    bool result = false;
    transform(word.begin(), word.end(), word.begin(), ::tolower); //lowercase word, because that's how it shows up in the dictionary.
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

/**
 * Convert coordinates in the form "Vh", where 'V' is the line and 'h' is the column, to x and y starting at 0.
 * @param coord Coordinates in the form "Vh".
 * @param x Corresponding x coordinate.
 * @param y Corresponding y coordinate.
 */
void convertCoordinates(const string &coord, int &x, int &y) {
    y = coord[0] - 'A';
    x = coord[1] - 'a';
}

/**
 * Determine if a given word will fit in the board as if it were empty, starting at (x,y) and moving in (direction). Assumes the starting
 * position is valid.
 * @param board The board in which to put the word.
 * @param word The word to try to fit in.
 * @param x The starting x coordinate.
 * @param y The starting y coordinate.
 * @param direction The direction of the word starting from (x,y).
 * @return True if the word will fit.
 */
bool outOfBounds(const Board &board, const string &word, int x, int y, const char &direction){
    if(direction == 'V')
        y += word.size() - 1;
    else
        x += word.size() - 1;
    return !board.validPos(x,y);
}

/**
 * Try to add a word to the board, starting at (x,y) and moving in (direction), aware of its surroundings. Write it in if possible.
 * Decompose the analysis of the legality of the word in 3 parts: head, body and tail. Head and tail are symmetric, so
 * they can be handled simultaneously and clearly. The body must check for "word crossing" and accept it if it's legal.
 * Important note: refactoring of the function was attempted to avoid writing similar code twice, but it would compromise
 * readability so it was decided to keep it this way.
 * @param board The board to which to add word if possible.
 * @param word The word to write to the board.
 * @param x The starting x coordinate of the word.
 * @param y The starting y coordinate of the word.
 * @param direction The direction of the word starting from (x,y).
 * @return True if the write operation is succeeded.
 */
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

/**
 * Using I/O, ask for the 3 defining features of a word insertion (word, start, direction) and handle them accordingly.
 * If successful in adding the word to the board, save said features to the parameter vectors for later storage.
 * @param board The board to which a word is to be added.
 * @param vWords The collection of vertical words ordered by input.
 * @param hWords The collection of horizontal words ordered by input.
 * @param vCoords The matching collection of vertical starting coordinates.
 * @param hCoords The matching collection of horizontal starting coordinates.
 */
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

/**
 * Save the board content to BOARD.txt, including a 2D representation of it.
 * @param board The board to be saved.
 * @param vWords The collection of vertical words ordered by input.
 * @param hWords The collection of horizontal words ordered by input.
 * @param vCoords The matching collection of vertical starting coordinates.
 * @param hCoords The matching collection of horizontal starting coordinates.
 */
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
    do { //adding words to board one at a time
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