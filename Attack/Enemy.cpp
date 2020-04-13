#include "Enemy.h"

Enemy::Enemy() {}

Enemy::Enemy(Animation &a, Animation &b, int X, int Y, int dir_, int lvl)
	: Tank(a, b, X, Y, dir_, lvl)
{
	dir = rand() % 4 + 1;
	army = "enemy";
}

Enemy::~Enemy() {}

void Enemy::update(double time)
{
	int speed;
	switch (dir)
	{
	case 1:
		accelerate(1, -0.05 * time);
		if (y <= 32)
		{
			traffic.up.dir = false;
			changeDir();
		}
		else
			traffic.up.dir = true;
		break;
	case 2:
		accelerate(2, 0.05 * time);
		if (x >= 1888)
		{
			traffic.right.dir = false;
			changeDir();
		}
		else
			traffic.right.dir = true;
		break;
	case 3:
		accelerate(3, 0.05 * time);
		if (y >= 1048)
		{
			traffic.down.dir = false;
			changeDir();
		}
		else 
			traffic.down.dir = true;
		break;
	case 4:
		accelerate(4, -0.05 * time);
		if (x <= 32)
		{
			traffic.left.dir = false;
			changeDir();
		}
		else
			traffic.left.dir = true;
		break;
	}

	Tank::update(time);
}

void Enemy::changeDir()
{
	int d;
	while (true)
	{
		d = rand() % 4 + 1;
		if (dir != d)
			break;
	}
	dir = d;
}