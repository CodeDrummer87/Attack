#include "Player.h"

Player::Player() {}

Player::Player(Animation &a, Animation &b, int X, int Y, int dir_, string army_, int lvl)
	: Tank(a, b, X, Y, dir_, army_, lvl)
{
	totalKills = currentExperience = 0;
	if (level > 1)
		experience = pow(2, level - 1);
	else
		experience = 2;

	hasRank = preferment = false;
}

Player::~Player() {}

void Player::update(double time)
{
	if (currentExperience >= experience)
		preferment = true;
	if (preferment)
	{
		int residual_ = currentExperience - experience > 0 ? (currentExperience - experience) : 0;
		improveTank(residual_);
	}
	
	Tank::update(time);
}

void Player::nickDown(int exp)
{
	++totalKills;
	currentExperience += exp;
}

void Player::improveTank(int residual)
{
	++level;
	status = ALIVE;
	hitPoints = level + 1;
	experience *= 2;
	currentExperience = residual;
}