#include "Player.h"
#include <vector>
using namespace std;

Player::Player(int NumPlayers)
{
	this->NumPlayers = NumPlayers;
	vector<char> players;
	players.resize(NumPlayers, '\0');
	vector<int> score;
	score.resize(NumPlayers, '\0');
}
