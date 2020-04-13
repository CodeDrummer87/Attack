#include "Enemy.h"

Enemy::Enemy() {}

Enemy::Enemy(Animation &a, Animation &b, int X, int Y, int dir_, int lvl)
	: Tank(a, b, X, Y, dir_, lvl)
{
	dir = rand() % 4 + 1;
	army = "enemy";
	currentDir = dir;
}

Enemy::~Enemy() {}

void Enemy::update(double time)
{
	switch (dir)
	{
	case 1:
		if (y <= 32)
			traffic.up.dir = false;
		else
			traffic.up.dir = true;
		break;
	case 2:
		if (x >= 1888)
			traffic.right.dir = false;
		else
			traffic.right.dir = true;
		break;
	case 3:
		if (y >= 1048)
			traffic.down.dir = false;
		else 
			traffic.down.dir = true;
		break;
	case 4:
		if (x <= 32)
			traffic.left.dir = false;
		else
			traffic.left.dir = true;
		break;
	}

	if (!checkDir())
		changeDir();

	Tank::update(time);
}

bool Enemy::checkDir()
{
	bool clear = true;
	if (!traffic.up.dir || !traffic.right.dir || !traffic.down.dir || !traffic.left.dir)
		clear = false;
	return clear;
}

void Enemy::changeDir()
{
	int dir_;
	while (true)
	{
		dir_ = rand() % 4 + 1;
		if (dir_ != currentDir)
			break;
	}
	dir = dir_;
	currentDir = dir;
}