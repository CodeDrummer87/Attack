#pragma once

#include "Enemy.h"

Enemy::Enemy()
{}

Enemy::Enemy(Animation &a, double x_, double y_, string name_, int dir_, bool isPlayAnimation_, Animation &b,
	string army_, int lvl, bool isDoubleCannon_) : Tank(a, x_, y_, name_, dir_, isPlayAnimation_, b, army_, lvl)
{
	round = false;
	isDoubleCannon = isDoubleCannon_;
	
	defeatDistance = 9 + level;
	updateDestinationDistance();
}

Enemy::~Enemy()
{}

EvilTank Enemy::evilTank = { false, NULL, 0 };

void Enemy::update(double time)
{
	float speed = level % 2 == 0 ? 0.09 : 0.08;

	if (name != "destroyed")
	{
		switch (dir)
		{
		case 1:
			if (traffic.up.dir)
				accelerate(1, -speed * time);
			else
				changeDir();
			break;
		case 2:
			if (traffic.right.dir)
				accelerate(2, speed * time);
			else
				changeDir();
			break;
		case 3:
			if (traffic.down.dir)
				accelerate(dir, speed * time);
			else
				changeDir();
			break;
		case 4:
			if (traffic.left.dir)
				accelerate(dir, -speed * time);
			else
				changeDir();
			break;
		}

		reachedDist += speed * time;
		if (reachedDist >= destinationDist)
		{
			changeDir();
			updateDestinationDistance();
		}
	}

	Tank::update(time);
}

void Enemy::changeDir()
{
	srand(time(NULL));

	int k = rand() % 100 + 1;
	if (k <= 25)
	{
		dir++;
		if (dir > 4)
			dir = 1;
	}
	else if (k > 25 && k <= 50)
	{
		dir--;
		if (dir < 1)
			dir = 4;
	}
	else if (k > 50 && k <= 75)
	{
		dir += 2;
		if (dir > 4)
			dir -= 4;
	}
	else
	{
		dir += 3;
		if (dir > 4)
			dir -= 4;
	}
}

void Enemy::checkMapCollision(string * map)
{
	if (dir == 1)
		for (int i = (y - 20) / 32; i <= (y + 20) / 32; i++)
			for (int j = (x - 2) / 32; j <= (x + 30) / 32; j++)
			{
				if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
					traffic.up.dir = false;

				if (!traffic.down.dir)
					traffic.down.dir = true;
			}

	if (dir == 3)
		for (int i = (y + 20) / 32; i <= (y + 50) / 32; i++)
			for (int j = (x - 2) / 32; j <= (x + 30) / 32; j++)
			{
				if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
					traffic.down.dir = false;

				if (!traffic.up.dir)
					traffic.up.dir = true;
			}

	if (dir == 4)
		for (int i = (y) / 32; i <= (y + 30) / 32; i++)
			for (int j = (x - 16) / 32; j <= (x + 20) / 32; j++)
			{
				if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
					traffic.left.dir = false;

				if (!traffic.right.dir)
					traffic.right.dir = true;
			}

	if (dir == 2)
		for (int i = (y) / 32; i <= (y + 30) / 32; i++)
			for (int j = (x + 42) / 32; j <= (x + 50) / 32; j++)
			{
				if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
					traffic.right.dir = false;
				
				if (!traffic.left.dir)
					traffic.left.dir = true;
			}
}

void Enemy::updateDestinationDistance()
{	
	reachedDist = 0.0;
	destinationDist = abs(y - x) + (level + number) * 2;
	while (destinationDist > 1200)
		destinationDist /= 2;
	if (destinationDist < 300)
		destinationDist += 400;
}

void Enemy::checkMapTarget(string *map)
{
	int dest = 0;

	if (!round)
	{
		if (dir == 1)
			for (int i = (y - 20) / 32; i <= (y + 20) / 32;)
				for (int j = (x - 2) / 32; j <= (x + 30) / 32;)
				{
					dest = i - defeatDistance > 0 ? i - defeatDistance : 0;
					while (i > dest)
					{
						if (map[i][j] == 'b')
						{
							round = true;
							return;
						}
						i--;
					}
					return;
				}

		if (dir == 4)
			for (int i = (y) / 32; i <= (y + 30) / 32; i++)
				for (int j = (x - 16) / 32; j <= (x + 20) / 32; j++)
				{
					dest = j - defeatDistance > 0 ? j - defeatDistance : 0;
					while (j > dest)
					{
						if (map[i][j] == 'b')
						{
							round = true;
							return;
						}
						j--;
					}
					return;
				}

		if (dir == 2)
			for (int i = (y) / 32; i <= (y + 30) / 32; i++)
				for (int j = (x + 42) / 32; j <= (x + 50) / 32; j++)
				{
					dest = j + defeatDistance < 60 ? j + defeatDistance : 60;
					while (j < dest)
					{
						if (map[i][j] == 'b')
						{
							round = true;
							return;
						}
						j++;
					}
					return;
				}
	}
}

void Enemy::destroyBrickWalls(string *map)
{
	int d;
	int ty = y / 32;
	int tx = x / 32;

	if (!round)
	{
		if (dir == 1)
		{
			d = ty - defeatDistance > 0 ? ty - defeatDistance : 1;
			while (ty > d)
			{
				if (map[ty][tx] == 'B') return;

				if (map[ty][tx] == 'b')
				{
					round = true;
					return;				
				}
				ty--;
			}
			return;
		}

		if (dir == 3)
		{
			d = ty + defeatDistance < 119 ? ty + defeatDistance : 118;
			while (ty < d)
			{
				if (map[ty][tx] == 'B') return;

				if (map[ty][tx] == 'b')
				{
					round = true;
					return;
				}
				ty++;
			}
			return;
		}
	}
}
