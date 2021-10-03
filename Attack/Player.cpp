#include "Player.h"


Player::Player()
{}

Player::Player(Animation &anim, double x_, double y_, string name_, int dir_, bool isPlayAnimation_,
	Animation &aExplosion, string army_, int level_) : Tank(anim, x_, y_, name_, dir_, isPlayAnimation_, aExplosion, army_, level_)
{
	totalKills = 0;
	currentExperience = 0;

	if (level > 1)
		requiredExperience = level < 30 ? pow(2, level - 1) : 600000000;
	else
		requiredExperience = 2;

	hasRank = isPreferment = isCommander = false;
}

Player::~Player()
{}

void Player::update(double time)
{
	if (currentExperience >= requiredExperience)
		isPreferment = true;
	if (isPreferment)
	{
		int residual_ = currentExperience - requiredExperience > 0 ? (currentExperience - requiredExperience) : 0;
		improveTank(residual_);
	}

	Tank::update(time);
}

void Player::setStartPosition(double x_, double y_)
{
	this->x = x_;
	this->y = y_;
	this->dir = 1;
}

void Player::checkIconCollision(string map[], Sound &sound)
{
	for (int i = (anim.getRect(dir).top + 15) / 32; i < (y + anim.getRect(dir).height) / 32; i++)
		for (int j = (anim.getRect(dir).left + 14) / 32; j < (x + anim.getRect(dir).width) / 32; j++)
		{
			if (map[i][j] == 'U')
			{
				sound.play();
				this->isPreferment = true;
				map[i][j] = ' ';
			}
		}
}

void Player::improveTank(int residual)
{
	++level;
	hitPoints = level + 1;
	if (requiredExperience <= 599999999)
	{
		requiredExperience *= 2;
		currentExperience = residual;
	}
	else
		currentExperience = 0;
}
