#pragma once
#include <vector>
#include "Pool.h"

class Player
{
public:
	unsigned getScore() const;
	void setScore(const unsigned& score);
	void drawTile(Pool& pool);
	void endGame();
private:
	unsigned score;
	std::vector<char> hand;
};
