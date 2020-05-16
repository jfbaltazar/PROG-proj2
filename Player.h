#pragma once
#include <vector>

class Player
{
private:
	int NumPlayers;
	vector<char> players;
	vector<int> score;
public:
	explicit Player(int NumPlayers);
};
