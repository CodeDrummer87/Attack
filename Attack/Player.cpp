#include "Player.h"
#include <iostream>

using namespace std;

Player::Player() {}

Player::Player(Animation &a, Animation &b, int X, int Y, int dir_, string army_, int lvl)
	: Tank(a, b, X, Y, dir_, army_, lvl)
{
	totalKills = currentKillCounter = 0;
	experience = 5;
}

Player::~Player() {}

void Player::update(double time)
{
	Tank::update(time);
}

void Player::nickDown()
{
	++totalKills;
	++currentKillCounter;
}