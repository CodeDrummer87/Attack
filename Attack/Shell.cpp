#include "Shell.h"


Shell::Shell()
{}

Shell::Shell(Animation &a, Animation &b, Tank *tank)
{
	dist = 0.0f;
	name = "shell";
	army = tank->army;
	anim = a;
	aExplosion = b;
	dir = tank->dir;
	own = tank;
	x = tank->getCoordX(true);
	y = tank->getCoordY(true);
	anim.sprite.setPosition(x, y);
	isExist = isPlayAnimation = true;
	level = tank->level;
	isExplosion = false;
	status = ALIVE;
}

Shell::~Shell()
{}

void Shell::update(double time)
{
	if (status == ALIVE)
	{
		if (dir == 1)
		{
			dx = 0;
			dy = -0.5 * time - ((double)level / 5);
			dist -= dy;
		}
		if (dir == 2)
		{
			dy = 0;
			dx = 0.5 * time + ((double)level / 5);
			dist += dx;
		}
		if (dir == 3)
		{
			dx = 0;
			dy = 0.5 * time + ((double)level / 5);
			dist += dy;
		}
		if (dir == 4)
		{
			dy = 0;
			dx = -0.5 * time - ((double)level / 5);
			dist -= dx;
		}

		if (abs(dist) >= 350 + (float)level * 50)
			isExplosion = true;

		if (isExplosion)
		{
			status = WOUNDED;
			anim = aExplosion;
			name = "explosion";
			dir = rand() % 360;
		}

		x += dx;
		y += dy;
	}
	else if (status == WOUNDED)
		if (anim.isEnd(time))
		{
			isExist = false;
			own->isShot = true;
		}
}
