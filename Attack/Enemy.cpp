#pragma once

#include "Enemy.h"

Enemy::Enemy()
{}

Enemy::Enemy(Animation &a, double x_, double y_, string name_, int dir_, bool isPlayAnimation_, SoundBuffer &sExplosion_, int expFrameCount,
	string army_, int lvl) : Tank(a, x_, y_, name_, dir_, isPlayAnimation_, sExplosion_, expFrameCount, army_, lvl)
{
	isPlayerControl = false;
	round = false;
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
	case 1:
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

	case 2:
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

	case 3:
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

	case 4:
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

void Enemy::destroyPlayersTanks(Tank *p)
{
	if (p->name != "destroyed")
	{
		switch (dir)
		{
		case 1:
			if (y - p->getCoordY(false) <= 350 + (float)level * 50 && x > p->getCoordX(false) - 32 && x < p->getCoordX(false) + 32)
			{
				round = y > p->getCoordY(false) ? true : false;
				return;
			}

		case 2:
			if (p->getCoordX(false) - x <= 350 + (float)level * 50 && y > p->getCoordY(false) - 32 && y < p->getCoordY(false) + 32)
			{
				round = x < p->getCoordX(false) ? true : false;
				return;
			}

		case 3:
			if (p->getCoordY(false) - y <= 350 + (float)level * 50 && x > p->getCoordX(false) - 32 && x < p->getCoordX(false) + 32)
			{
				round = y < p->getCoordY(false) ? true : false;
				return;
			}

		case 4:
			if (x - p->getCoordX(false) <= 350 + (float)level * 50 &&
				y > p->getCoordY(false) - 32 && y < p->getCoordY(false) + 32)
			{
				round = x > p->getCoordX(false) ? true : false;
				return;
			}
		}
	}
}
