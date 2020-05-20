#include "Player.h"

unsigned Player::getScore() const {
	return this->score;
}

void Player::setScore(const unsigned& newScore) {
	this->score = newScore;
}

void Player::drawTile(Pool& pool) {
	this->hand.push_back(pool.extractTile());
}

void Player::endGame()
{
	this->hand.empty()
}
