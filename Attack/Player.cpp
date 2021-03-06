#include "Player.h"

Player::Player() {}

Player::Player(Animation &a, Animation &b, double X, double Y, int dir_, int lvl, const int W, const int H)
	: Tank(a, b, X, Y, dir_, lvl, W, H)
{
	army = "player";
	totalKills = currentExperience = 0;
	if (level > 1)
		experience = pow(2, level - 1);
	else
		experience = 2;

	hasRank = preferment = isCommander  = false;

	isAirSpotter = isTargetCreated = false;
	xTargetPosition = yTargetPosition = 0;
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
	
	if (!isAirSpotter)
	{
		Tank::update(time);
	}
	else
	{
		if (xTargetPosition == 0 && yTargetPosition == 0)
		{
			xTargetPosition = x;
			yTargetPosition = y;
		}

		switch (dir)
		{
		case 1: dy = -0.09 * time - ((double)level / 100);
			break;
		case 2: dx = 0.09 * time + ((double)level / 100);
			break;
		case 3: dy = 0.09 * time + ((double)level / 100);
			break;
		case 4: dx = -0.09 * time - ((double)level / 100);
			break;
		}

		xTargetPosition += dx * 5;
		if (xTargetPosition < 200)
		{
			xTargetPosition = 200;
		}
		else if (xTargetPosition > mapWidth - 200)
		{
			xTargetPosition = mapWidth - 200;
		}

		yTargetPosition += dy * 5;
		if (yTargetPosition < 200 + 34 * 32)	// Screen height is equal 34 squares (32px, 32px)
		{
			yTargetPosition = 200 + 34 * 32;
		}
		else if (yTargetPosition > mapHeight - 200)
		{
			yTargetPosition = mapHeight - 200;
		}
		dx = dy = 0;
	}
}

void Player::nickDown(int exp)
{
	++totalKills;
	currentExperience += exp;
}

void Player::improveTank(int residual)
{
	++level;
	hitPoints = level + 1;
	experience *= 2;
	currentExperience = residual;
}