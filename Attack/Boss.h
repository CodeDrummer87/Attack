#pragma once

#include "Enemy.h"

struct BossArgs
{
	Animation &anim;
	double x;
	double y;
	string name;
	int dir;
	bool isPlayAnimation;
	Animation &aExplosion;
	int level;
	Animation &aTower;
	Animation &aTowerCrash;
};

class Boss : public Enemy
{
private:
	Animation aTower;
	Animation aTowerCrash;
	int rot;

public:
	//.:: Constructor :::::::::::::::::::::::
	Boss();
	Boss(BossArgs&);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Boss();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);
	void draw(RenderWindow&);

};
