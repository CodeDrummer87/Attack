#pragma once

#include "Shell.h"
#include "Player.h"
#include "Enemy.h"

extern View view;

Shell::Shell()
{}

Shell::Shell(Animation &a, Animation &b, Tank *tank)
{
	z_index = 1;

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
		if (dir == 0)
		{
			dx = 0;
			dy = -0.5 * time - ((double)level / 5) - own->shellSpeedBonus;
			dist -= dy;
		}
		if (dir == 90)
		{
			dy = 0;
			dx = 0.5 * time + ((double)level / 5) + own->shellSpeedBonus;
			dist += dx;
		}
		if (dir == 180)
		{
			dx = 0;
			dy = 0.5 * time + ((double)level / 5) + own->shellSpeedBonus;
			dist += dy;
		}
		if (dir == 270)
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

void Shell::damageVehicle(GroundVehicle *t, Sound &armorSound)
{
	if (army != t->army)
	{
		double tX = (t->dir == 0 || t->dir == 180) ? t->getCoordX(false) - 19 : t->getCoordX(false) - 25;
		double tY = (t->dir == 0 || t->dir == 180) ? t->getCoordY(false) - 25 : t->getCoordY(false) - 19;
		
		FloatRect vehicle = (t->dir == 0 || t->dir == 180) ? FloatRect(tX, tY, 37, 49) : FloatRect(tX, tY, 49, 37);
		FloatRect shell = (dir == 0 || dir == 180) ? FloatRect(x - 2, y - 4, 3, 7) : FloatRect(x - 4, y - 2, 7, 3);

		if (shell.intersects(vehicle))
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

					if (army == "enemy" && own->name == "tank")
					{
						this->paintOwn();
						static_cast<Enemy*>(own)->round = false;
					}
					else
						conveyExperience(t->level);
				}

				if (army == "player" && dir == t->dir)
					static_cast<Enemy*>(t)->dir = getCounterDirection(dir);

			}
			isExist = false;
			if (name == "shell")
				own->isShot = true;
		}
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

void Shell::damageBoss(GroundVehicle *boss_, Sound &armorSound, Sound &armorResistSound)
{
	if (army != boss_->army)
	{
		double tX = (boss_->dir == 0 || boss_->dir == 180) ? boss_->getCoordX(false) - 42 : boss_->getCoordX(false) - 51;
		double tY = (boss_->dir == 0 || boss_->dir == 180) ? boss_->getCoordY(false) - 51 : boss_->getCoordY(false) - 42;

		FloatRect boss = (boss_->dir == 0 || boss_->dir == 180) ? FloatRect(tX, tY, 83, 101) : FloatRect(tX, tY, 101, 83);
		FloatRect shell = (dir == 0 || dir == 180) ? FloatRect(x - 2, y - 4, 3, 7) : FloatRect(x - 4, y - 2, 7, 3);

		if (shell.intersects(boss))
		{
			if (dir == getCounterDirection(boss_->dir))
			{
				armorResistSound.play();
			}
			else
			{
				armorSound.play();
				if (level >= boss_->hitPoints && boss_->hitPoints > 1)
					boss_->hitPoints = 1;
				else
					boss_->hitPoints -= level;

				if (boss_->hitPoints <= 0)
				{
					if (own->shellSpeedBonus < 7.5f && abs(dist) >= 335 + (float)level * 30)
					{
						own->shellSpeedBonus += 1.5f;
						own->isShowSniperAchiev = true;
					}

					conveyExperience(boss_->level);
				}

				if (army == "player" && dir == boss_->dir)
					static_cast<Enemy*>(boss_)->dir = getCounterDirection(boss_->dir);
			}
			isExist = false;
			if (name == "shell")
				own->isShot = true;
		}
	}
}
