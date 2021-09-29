#include "Tank.h"


Tank::Tank()
{}

Tank::Tank(Animation &anim, double x_, double y_, string name_, int dir_, bool isPlayAnimation_,
	Animation &aExplosion, string army_)
	: Entity(anim, x_, y_, name_, dir_, isPlayAnimation_)
{
	aTankExplosion = aExplosion;
	army = army_;

	destroyed = false;
	isShot = true;
	isSmoking = true;
}

Tank::~Tank()
{}

int Tank::counter = 0;
