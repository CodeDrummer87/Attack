#pragma once

#include "Enemy.h"

Enemy::Enemy()
{}

Enemy::Enemy(Animation &a, double x_, double y_, SoundBuffer &sExplosion_, int lvl) 
	: Tank(a, x_, y_, "tank", 180, true, sExplosion_, 12, "enemy", lvl)
{
	isPlayerControl = false;
	round = false;
	isInRadarCoverageArea = false;
	currentColor = Color::White;
}

Enemy::~Enemy()
{}

EvilTank Enemy::evilTank = { false, NULL, 0 };

void Enemy::destroyBrickWalls(string *map)
{
	int tX = x / 32;
	int tY = y / 32;
	int dist;

	switch (dir)
	{
	case 0:
		dist = tY - 3;
		while (tY > dist)
		{
			if (map[tY][tX] == 'B')
				return;
			if (map[tY][tX] == 'b')
			{
				round = true;
				return;
			}

			tY--;
		}

		return;

	case 90:
		dist = tX + 3;
		while (tX < dist)
		{
			if (map[tY][tX] == 'B' || map[tY+1][tX] ==  'B')
				return;
			if (map[tY][tX] == 'b' || map[tY + 1][tX] == 'b')
			{
				round = true;
				return;
			}

			tX++;
		}

		return;

	case 180:
		dist = tY + 3;
		while (tY < dist)
		{
			if (map[tY][tX] == 'B')
				return;
			if (map[tY][tX] == 'b')
			{
				round = true;
				return;
			}

			tY++;
		}

		return;

	case 270:
		dist = tX - 3;
		while (tX > dist)
		{
			if (map[tY][tX] == 'B' || map[tY + 1][tX] == 'B')
				return;
			if (map[tY][tX] == 'b' || map[tY + 1][tX] == 'b')
			{
				round = true;
				return;
			}

			tX--;
		}

		return;
	}
}

void Enemy::destroyPlayerTanks(Tank *p)
{
	if (p->name != "destroyed")
	{
		switch (dir)
		{
		case 0:
			if (y - p->getCoordY(false) <= 350 + (float)level * 50 && x > p->getCoordX(false) - 32 && x < p->getCoordX(false) + 32)
			{
				round = y > p->getCoordY(false) ? true : false;
				return;
			}

		case 90:
			if (p->getCoordX(false) - x <= 350 + (float)level * 50 && y > p->getCoordY(false) - 32 && y < p->getCoordY(false) + 32)
			{
				round = x < p->getCoordX(false) ? true : false;
				return;
			}

		case 180:
			if (p->getCoordY(false) - y <= 350 + (float)level * 50 && x > p->getCoordX(false) - 32 && x < p->getCoordX(false) + 32)
			{
				round = y < p->getCoordY(false) ? true : false;
				return;
			}

		case 270:
			if (x - p->getCoordX(false) <= 350 + (float)level * 50 &&
				y > p->getCoordY(false) - 32 && y < p->getCoordY(false) + 32)
			{
				round = x > p->getCoordX(false) ? true : false;
				return;
			}
		}
	}
}

void Enemy::update(double time)
{
	if (status != Status::DEAD)
	{
		z_index = isInRadarCoverageArea ? 3 : 2;
		anim.sprite.setColor(isInRadarCoverageArea ? Color(0, 255, 0, 210) : currentColor);
	}

	Tank::update(time);
}

void Enemy::applyCamouflage()
{
	currentColor = Color(250, 128, 114);
	anim.sprite.setColor(currentColor);
}
