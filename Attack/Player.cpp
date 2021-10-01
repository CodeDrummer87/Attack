#include "Player.h"


Player::Player()
{}

Player::Player(Animation &anim, double x_, double y_, string name_, int dir_, bool isPlayAnimation_,
	Animation &aExplosion, string army_, int level_) : Tank(anim, x_, y_, name_, dir_, isPlayAnimation_, aExplosion, army_, level_)
{
	totalKills = 0;
	currentExperience = 0;
	requiredExperience = 0;

	hasRank = preferment = isCommander = false;
}

Player::~Player()
{}

void Player::update(double time)
{
	Tank::update(time);
}

void Player::setStartPosition(double x_, double y_)
{
	this->x = x_;
	this->y = y_;
	this->dir = 1;
}
