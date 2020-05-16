#pragma once
#include <vector>
#define MAX_HAND_SIZE 7

class Player
{
private:
	unsigned score;
	char hand[MAX_HAND_SIZE];
public:
	unsigned getScore() const;
	void setScore(const unsigned& score);
};
