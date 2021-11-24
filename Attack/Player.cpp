#pragma once

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

AirSpotter Player::airSpotter = { false, NULL, false, 0.0, 0.0 };

void Player::update(double time)
{
	if (currentExperience >= requiredExperience)
		isPreferment = true;
	if (isPreferment)
	{
		int residual_ = currentExperience - requiredExperience > 0 ? (currentExperience - requiredExperience) : 0;
		improveTank(residual_);
	}

	if (airSpotter.isAirSpotter && airSpotter.currentPlayer == this)
	{
		if (isPlayAnimation)
			isPlayAnimation = false;

		if (airSpotter.xTargetPosition == 0.0 && airSpotter.yTargetPosition == 0.0)
		{
			airSpotter.xTargetPosition = x;
			airSpotter.yTargetPosition = y;
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

		airSpotter.xTargetPosition += dx * 5;
		if (airSpotter.xTargetPosition < 200)
		{
			airSpotter.xTargetPosition = 200;
		}
		else if (airSpotter.xTargetPosition > 61*32 - 200)
		{
			airSpotter.xTargetPosition = 61*32 - 200;
		}

		airSpotter.yTargetPosition += dy * 5;
		if (airSpotter.yTargetPosition < 200 + 34 * 32)	// Screen height is equal 34 squares (32px, 32px)
		{
			airSpotter.yTargetPosition = 200 + 34 * 32;
		}
		else if (airSpotter.yTargetPosition > 119*32 - 200)
		{
			airSpotter.yTargetPosition = 119 * 32 - 200;
		}
		dx = dy = 0;
	}
	else
	{
		Tank::update(time);
	}
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

			if (map[i][j] == 'R')
			{
				if (hitPoints < 1 + level)
				{
					sound.play();
					++hitPoints;
					isShowRepair = true;
					map[i][j] = ' ';
				}
			}

			if (map[i][j] == 'C')
			{
				if (Tank::camera != Camera::Target && Tank::camera != Camera::FirstPlane)
				{
					sound.play();
					this->isCommander = true;
					Tank::camera = Camera::Commander;
					map[i][j] = ' ';
				}
			}

			if (map[i][j] == 'A')
			{
				if (!airSpotter.isAirSpotter && airSpotter.currentPlayer == NULL && airSpotter.yTargetPosition == 0.0)
				{
					sound.play();
					map[i][j] = ' ';

					airSpotter.isAirSpotter = true;
					airSpotter.currentPlayer = this;
					airSpotter.isTargetCreated = true;
				}
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

void Player::defineNewCommander(vector<Player*> team)
{
	Player* newCommander = team[0];
	int lvl = 0;

	for (auto p : team)
	{
		if (p->status != DEAD && !p->isCommander)
		{
			if (p->level > lvl)
			{
				newCommander = p;
				lvl = p->level;
			}
		}
	}

	newCommander->isCommander = true;
}

bool Player::checkTeamForCommander(vector<Player*> team)
{
	for (auto p : team)
	{
		if (p->isCommander)
			return true;
	}

	return false;
}

void Player::checkMapCollision(string *map)
{
	if (dy < 0)
		for (int i = (y - 20) / 32; i <= (y + 20) / 32; i++)
			for (int j = (x - 2) / 32; j <= (x + 30) / 32; j++)
				if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
					dy = 0;

	if (dy > 0)
		for (int i = (y + 20) / 32; i <= (y + 50) / 32; i++)
			for (int j = (x - 2) / 32; j <= (x + 30) / 32; j++)
				if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
					dy = 0;

	if (dx < 0)
		for (int i = (y) / 32; i <= (y + 30) / 32; i++)
			for (int j = (x - 16) / 32; j <= (x + 20) / 32; j++)
				if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
					dx = 0;

	if (dx > 0)
		for (int i = (y) / 32; i <= (y + 30) / 32; i++)
			for (int j = (x + 42) / 32; j <= (x + 50) / 32; j++)
				if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
					dx = 0;
}

void Player::nickDown(int exp)
{
	++totalKills;
	currentExperience += exp;
}
