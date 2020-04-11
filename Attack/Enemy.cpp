#include "Enemy.h"

Enemy::Enemy() {}

Enemy::Enemy(Animation &a, Animation &b, int X, int Y, int dir_, int lvl)
	: Tank(a, b, X, Y, dir_, lvl)
{
	army = "enemy";
}

Enemy::~Enemy() {}

void Enemy::update(double time)
{
	Tank::update(time);
}