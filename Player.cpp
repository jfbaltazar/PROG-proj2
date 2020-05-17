#include "Player.h"
#include <vector>
using namespace std;

unsigned Player::getScore() const
{
	return this->score;
}

void Player::setScore(const unsigned &score)
{
	this->score = score;
}
