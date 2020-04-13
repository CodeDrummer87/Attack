#include "Enemy.h"

Enemy::Enemy() {}

Enemy::Enemy(Animation &a, Animation &b, int X, int Y, int dir_, int lvl)
	: Tank(a, b, X, Y, dir_, lvl)
{
	dir = rand() % 4 + 1;
	army = "enemy";
	round = false;
}

Enemy::~Enemy() {}

void Enemy::update(double time)
{
	int speed;
	switch (dir)
	{
	case 1:
		if (y <= 32)
			traffic.up.dir = false;
		if (traffic.up.dir)
			accelerate(1, -0.05 * time);
		else
			changeDir();
		break;
	case 2:
		if (x >= 1888)
			traffic.right.dir = false;
		if (traffic.right.dir)
			accelerate(2, 0.05 * time);
		else
			changeDir();
		break;
	case 3:
		if (y >= 1048)
			traffic.down.dir = false;
		if (traffic.down.dir)
			accelerate(dir, 0.05 * time);
		else
			changeDir();
		break;
	case 4:
		if (x <= 32)
			traffic.left.dir = false;
		if (traffic.left.dir)
			accelerate(dir, -0.05 * time);
		else
			changeDir();
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

void Enemy::enemyCollide(Entity* e)
{
	switch (dir)
	{
	case 1: 
		if (e->dir == 3)
			traffic.up.dir = false;
		changeDir();
		break;
	case 2: 
		if (e->dir == 4)
			traffic.right.dir = false;
		changeDir();
		break;
	case 3:
		if (e->dir == 1)
			traffic.down.dir = false;
		changeDir();
		break;
	case 4:
		if (e->dir == 2)
			traffic.left.dir = false;
		changeDir();
		break;
	}
}

void Enemy::clearAllDirections()
{
	traffic.up.dir = traffic.right.dir = traffic.down.dir = traffic.left.dir = true;
}