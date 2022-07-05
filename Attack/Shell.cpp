#pragma once

#include "Shell.h"
#include "Player.h"
#include "Enemy.h"

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
	number = own->number;
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
			dy = -0.5 * time - ((double)level / 5) - own->shellSpeedBonus;
			dist -= dy;
		}
		if (dir == 2)
		{
			dy = 0;
			dx = 0.5 * time + ((double)level / 5) + own->shellSpeedBonus;
			dist += dx;
		}
		if (dir == 3)
		{
			dx = 0;
			dy = 0.5 * time + ((double)level / 5) + own->shellSpeedBonus;
			dist += dy;
		}
		if (dir == 4)
		{
			dy = 0;
			dx = -0.5 * time - ((double)level / 5) - own->shellSpeedBonus;
			dist -= dx;
		}

		if (abs(dist) >= 350 + (float)level * 30)
			isExplosion = true;

		if (isExplosion)
		{
			status = WOUNDED;
			anim = aExplosion;
			name = "explosion";
			dir = rand() % 360;

			//.:: Explosion volume depends on the distance to the camera :::::::
			if (army == "enemy")
			{
				if (y > view.getCenter().y - 20 * 32 && y < view.getCenter().y + 20 * 32)
					anim.sound.setVolume(50.f);
				else if (y > view.getCenter().y - 30 * 32 && y < view.getCenter().y - 20 * 32 ||
					y < view.getCenter().y + 30 * 32 && y > view.getCenter().y + 20 * 32)
					anim.sound.setVolume(15.f);
				else
					anim.sound.setVolume(0.f);
			}
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

void Shell::damageEntity(GroundVehicle *t, Sound &armorSound)
{
	if (army != t->army)
		if (anim.getShellRect(true).intersects(t->anim.getShellRect(false)))
		{
			armorSound.play();
			if (this->name == "shell" && (t->name == "tank" || t->name == "truck" || t->name == "boss"))
			{
				if (level >= t->hitPoints && t->hitPoints > 1)
					t->hitPoints = 1;
				else
					t->hitPoints -= level;

				if (t->hitPoints <= 0)
				{
					if (own->shellSpeedBonus < 7.5f && abs(dist) >= 335 + (float)level * 30) 
					{
						own->shellSpeedBonus += 1.5f;
						own->isShowSniperAchiev = true;
					}

					if (army == "enemy")
					{
						if (name == "tank")
							paintOwn();
						static_cast<Enemy*>(own)->round = false;
					}
					else
						conveyExperience(t->level);
				}

				if (army == "player" && dir == t->dir)
					static_cast<Enemy*>(t)->dir = t->dir + 2 <= 4 ? t->dir + 2 : t->dir - 2;
			}
			isExist = false;
			if (name == "shell")
				own->isShot = true;
		}
}

void Shell::conveyExperience(int experience)
{
	if (own->status != DEAD)
		static_cast<Player*>(own)->nickDown(experience);
}

void Shell::paintOwn()
{
	own->anim.sprite.setColor(Color::Yellow);
	if (own->army == "enemy")
	{
		Enemy::evilTank = { true, own, 0 };
		Tank::camera = MalevolentTank;
	}
} 
