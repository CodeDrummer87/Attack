#pragma once

#include "Shell.h"
#include "Player.h"
#include "Enemy.h"
#include "TankTower.h"
#include "Boss.h"

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

Shell::Shell(Animation &a, Animation &b, Tank *tank, short numberOfCannon_)
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
	numberOfCannon = numberOfCannon_;
	
	double X = tank->getCoordX(true);
	double Y = tank->getCoordY(true);
	
	if (numberOfCannon == (short)1)
	{
		x = dir == 0 ? X -= 8 : dir == 90 ? X += 27 : dir == 180 ? X -= 7 : X -= 27;
		y = dir == 0 ? Y -= 27 : dir == 90 ? Y -= 8 : dir == 180 ? Y += 27 : Y -= 8;
	}
	else
	{
		x = dir == 0 ? X += 8 : dir == 90 ? X += 27 : dir == 180 ? X += 8 : X -= 27;
		y = dir == 0 ? Y -= 27 : dir == 90 ? Y += 7 : dir == 180 ? Y += 27 : Y += 7;
	}
	
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
			own->name == "turret" && numberOfCannon == (short)1 ? static_cast<TankTower*>(own)->isFirstShot = true
				: own->name == "turret" && numberOfCannon == (short)2 ? static_cast<TankTower*>(own)->isSecondShot = true
				: own->isShot = true;
		}
}

void Shell::checkMapCollision(string map[])
{
	int w = dir == 90 || dir == 270 ? 4 : 2;
	int h = dir == 90 || dir == 270 ? 2 : 4;
	int X = (x - w) / 32;
	int Y = (y - h) / 32;

	bool isNearbyBarrier = false;
	dir == 0 && map[Y + 1][X] == 'b' ? map[Y + 1][X] = ' ', (map[Y + 1][X + 1] == 'b' ? map[Y + 1][X + 1] = ' ' : false), isExplosion = isNearbyBarrier = true
		: dir == 90 && map[Y][X - 1] == 'b' ? map[Y][X - 1] = ' ', isExplosion = isNearbyBarrier = true
		: dir == 180 && map[Y - 1][X] == 'b' ? map[Y - 1][X] = ' ', isExplosion = isNearbyBarrier = true
		: dir == 270 && map[Y][X + 1] == 'b' ? map[Y][X + 1] = ' ', (map[Y + 1][X + 1] == 'b' ? map[Y + 1][X + 1] = ' ' : false), isExplosion = isNearbyBarrier = true : false;
	
	(dir == 0 && map[Y + 1][X] == 'B') || (dir == 90 && map[Y][X - 1] == 'B')
		|| (dir == 180 && map[Y - 1][X] == 'B') || (dir == 270 && map[Y][X + 1] == 'B') ? isExplosion = true : false;
	
	if (isNearbyBarrier) return;

	if (map[Y][X] == 'b' || map[Y][X] == 'B')
	{
		isExplosion = true;
		if (map[Y][X] == 'b')
			map[Y][X] = ' ';
	}

	(dir == 90 || dir == 270) && map[Y + 1][X] == 'b' ? map[Y + 1][X] = ' ', isExplosion = true
		: (dir == 0 || dir == 180) && map[Y][X + 1] == 'b' ? map[Y][X + 1] = ' ', isExplosion = true : false;
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

					if (army == "enemy" && (own->name == "tank" || own->name == "turret"))
					{
						if (own->name == "tank") this->paintOwn();
						own->name == "turret" && numberOfCannon == (short)1 ? static_cast<TankTower*>(own)->roundFirst = false
							: own->name == "turret" && numberOfCannon == (short)2 ? static_cast<TankTower*>(own)->roundSecond = false
							: static_cast<Enemy*>(own)->round = false;
					}
					else
						conveyExperience(t->level);
				}

				if (army == "player" && dir == t->dir)
					t->dir = getCounterDirection(dir);

			}
			isExist = false;
			if (name == "shell")
				own->name == "turret" && numberOfCannon == (short)1 ? static_cast<TankTower*>(own)->isFirstShot = true
				: own->name == "turret" && numberOfCannon == (short)2 ? static_cast<TankTower*>(own)->isSecondShot = true
				: own->isShot = true;
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

				if (army == "player" && dir == boss_->dir && !static_cast<Boss*>(boss_)->isAiming)
					boss_->dir = getCounterDirection(boss_->dir);
			}
			isExist = false;
			if (name == "shell")
				own->isShot = true;
		}
	}
}
