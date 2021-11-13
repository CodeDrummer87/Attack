#include "Shell.h"

extern View view;

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

			//.:: Explosion volume depends on the distance to the camera :::::::
			if (y > view.getCenter().y - 20 * 32 && y < view.getCenter().y + 20 * 32)
				anim.sound.setVolume(50.f);
			else if (y > view.getCenter().y - 30 * 32 && y < view.getCenter().y - 20 * 32 ||
					 y < view.getCenter().y + 30*32 && y > view.getCenter().y + 20*32)
				anim.sound.setVolume(15.f);
			else
				anim.sound.setVolume(0.f);
			//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		}

		x += dx;
		y += dy;
	}
	else if (status == WOUNDED)
		if (anim.isEnd(time))
		{
			isExist = false;
			own->isShot = true;
			if (own->army == "enemy")
				own->isReloading = false;
		}
}

void Shell::checkMapCollision(string map[])
{
	static int neighborCoordX;
	static int neighborCoordY;

	for (int i = y / 32; i < (y + anim.getShellRect(dir).height) / 32; i++)
		for (int j = x / 32; j < (x + anim.getShellRect(dir).width) / 32; j++)
		{
			neighborCoordX = j;
			neighborCoordY = i;
			if (dir % 2 == 0)
				neighborCoordY = (i * 32 + 32) / 32;
			else
				neighborCoordX = (j * 32 + 32) / 32;

			if (map[i][j] == 'b' || map[i][j] == 'B')
			{
				static_cast<Shell*>(this)->isExplosion = true;
				if (map[i][j] == 'b')
					map[i][j] = ' ';
			}

			if (map[neighborCoordY][neighborCoordX] == 'b')
			{
				static_cast<Shell*>(this)->isExplosion = true;
				map[neighborCoordY][neighborCoordX] = ' ';
			}
		}
}
