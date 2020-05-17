#pragma once
#include <vector>
#include "Pool.h"

class Player
{
public:
	unsigned getScore() const;
	void setScore(const unsigned& score);
	void drawTile(Pool &pool);
private:
    unsigned score;
    std::vector<char> hand;
};
