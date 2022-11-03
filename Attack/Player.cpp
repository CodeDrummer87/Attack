#pragma once

#include "Player.h"

Player::Player()
{}

Player::Player(Animation &anim, double x_, double y_, string name_, int dir_, bool isPlayAnimation_, SoundBuffer &sExplosion_,
	int expFrameCount, string army_, int level_)
	: Tank(anim, x_, y_, name_, dir_, isPlayAnimation_, sExplosion_, expFrameCount, army_, level_)
{
	isPlayerControl = true;

	totalKills = 0;
	currentExperience = 0;

	if (level > 1)
		requiredExperience = level < 30 ? pow(2, level - 1) : 600000000;
	else
		requiredExperience = 2;

	hasRank = isPreferment = isCommander = isTowingBack = false;

	combo[3] = '\0';
	isKeyPressed = false;
	destroyedVehicle = NULL;
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
		case 0: dy = -0.09 * time - ((double)level / 100);
			break;
		case 90: dx = 0.09 * time + ((double)level / 100);
			break;
		case 180: dy = 0.09 * time + ((double)level / 100);
			break;
		case 270: dx = -0.09 * time - ((double)level / 100);
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
		if (isTowingBack)
		{
			towBack(time);
		}

		Tank::update(time);
	}
}

void Player::setStartPosition(double x_, double y_)
{
	this->x = x_;
	this->y = y_;
	this->dir = 0;
}

void Player::checkIconCollision(string map[], int index, Sound &sound)
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
					map[i][j] = index == 0 ? ' ' : 'S';
				}
			}

			if (map[i][j] == 'A')
			{
				if (!airSpotter.isAirSpotter && airSpotter.currentPlayer == NULL && airSpotter.yTargetPosition == 0.0)
				{
					sound.play();
					map[i][j] = index == 0 ? ' ' : 'S';

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

void Player::defineNewCommander(vector<Player*> &team)
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

void Player::nickDown(int exp)
{
	++totalKills;
	currentExperience += exp;
}

void Player::insertCodeSymbol(char ch)
{
	if (isKeyPressed)
		isKeyPressed = combo[0] == ch ? true : false;

	if (!isKeyPressed)
	{
		isKeyPressed = true;

		combo[2] = combo[1];
		combo[1] = combo[0];
		combo[0] = ch;
	}
}

bool Player::checkCollisionWithDestroyedTank(GroundVehicle *d)
{
	double dX = (d->dir == 0 || d->dir == 180) ? d->getCoordX(false) - 34 : d->getCoordX(false) - 40;
	double dY = (d->dir == 0 || d->dir == 180) ? d->getCoordY(false) - 40 : d->getCoordY(false) - 34;
	FloatRect destroyed = (d->dir == 0 || d->dir == 180) ? FloatRect(dX, dY, 68, 80) : FloatRect(dX, dY, 80, 68);

	double tX = (dir == 0 || dir == 180) ? x - 25 : x - 19;
	double tY = (dir == 0 || dir == 180) ? y - 19 : y - 25;
	FloatRect tank = (dir == 0 || dir == 180) ? FloatRect(tX, tY, 37, 49) : FloatRect(tX, tY, 49, 37);

	return tank.intersects(destroyed);
}

void Player::setTow(GroundVehicle *d, string cipher)
{
	isTowingBack = true;
	destroyedVehicle = d;
	currentCipher = cipher;
}

void Player::towBack(double time)
{
	if (currentCipher == "311")
	{
		accelerate(0, 0.045 * time);
		destroyedVehicle->setCoordY(y - 52);
	}

	if (currentCipher == "133")
	{
		accelerate(180, -0.045 * time);
		destroyedVehicle->setCoordY(y + 52);
	}

	if (currentCipher == "422")
	{
		accelerate(90, -0.045 * time);
		destroyedVehicle->setCoordX(x + 52);
	}

	if (currentCipher == "244")
	{
		accelerate(270, 0.045 * time);
		destroyedVehicle->setCoordX(x - 52);
	}
}

void Player::checkMapCollisionWhenTow(string *map)
{
	if (dir == 0)
		for (int i = (y + 30) / 32; i <= (y + 43) / 32; i++)
			for (int j = (x - 2) / 32; j <= (x + 30) / 32; j++)
			{
				if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
					traffic.up.dir = false;

				if (!traffic.down.dir)
					traffic.down.dir = true;
			}

	if (dir == 90)
		for (int i = (y) / 32; i <= (y + 30) / 32; i++)
			for (int j = (x - 8) / 32; j <= (x + 20) / 32; j++)
			{
				if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
					traffic.right.dir = false;

				if (!traffic.left.dir)
					traffic.left.dir = true;
			}

	if (dir == 180)
		for (int i = (y - 8) / 32; i <= (y - 20) / 32; i++)
			for (int j = (x - 2) / 32; j <= (x + 30) / 32; j++)
			{
				if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
					traffic.down.dir = false;

				if (!traffic.up.dir)
					traffic.up.dir = true;
			}

	if (dir == 270)
		for (int i = (y) / 32; i <= (y + 30) / 32; i++)
			for (int j = (x + 26) / 32; j <= (x + 40) / 32; j++)
			{
				if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
					traffic.left.dir = false;

				if (!traffic.right.dir)
					traffic.right.dir = true;
			}
}

void Player::controlOfTank(char dirCh, double acc, double time)
{
	if (!isTowingBack || (isTowingBack && checkTowingDirectionBan(dirCh)))
	{
		isTowingBack = false;
		destroyedVehicle = NULL;
		if (currentCipher == "311") traffic.up.dir = true;
		else if (currentCipher == "133") traffic.down.dir = true;
		else if (currentCipher == "422") traffic.right.dir = true;
		else if (currentCipher == "244") traffic.left.dir = true;
		currentCipher = { ' ', ' ', ' ' };

		insertCodeSymbol(dirCh);

		accelerate(
			(dirCh == '1' ? 0 : dirCh == '2' ? 90 : dirCh == '3' ? 180 : 270),
			acc * time);
	}
}

bool Player::checkTowingDirectionBan(char dirCh)
{
	switch (dirCh)
	{
	case '1': return currentCipher == "133" ? false : true;
	case '2': return currentCipher == "244" ? false : true;
	case '3': return currentCipher == "311" ? false : true;
	case '4': return currentCipher == "422" ? false : true;
	}
}
