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
	float speed;

	if (level % 2 == 0)
		speed = 0.08;
	else
		speed = 0.06;

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