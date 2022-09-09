#pragma once

#include "TankTower.h"
#include "Boss.h"

TankTower::TankTower()
{}

TankTower::TankTower(Animation &a, double x_, double y_, int dir_, SoundBuffer &turn, SoundBuffer &sExplosion_, int expFrameCount, GroundVehicle *own_)
	: Enemy(a, x_, y_, "turret", dir_, false, sExplosion_, expFrameCount, "enemy", own_->level)
{
	z_index = 3;
	own = own_;

	currentTarget = NULL;
	isTargetSearch = true;

	isFirstShot = isSecondShot = true;
	roundFirst = roundSecond = isMortarShootTime = false;
	mortarShootTime = 0;

	dir = 180;
}

TankTower::~TankTower()
{}

void TankTower::update(double time)
{
	if (isDestroyed)
	{
		if (isPlayAnimation)
			isPlayAnimation = false;
	}
	else
	{
		if (status != DEAD && !static_cast<Boss*>(own)->isAiming)
		{
			x = own->getCoordX(false);
			y = own->getCoordY(false);

			if (!isTargetSearch && (currentTarget != NULL || currentTarget->status != DEAD))
			{
				int angle = takeAim(currentTarget);
				if (dir != angle)
					getRotationDirection(dir, angle);			
			}
			else
				dir = own->dir;

			if (currentTarget != NULL && currentTarget->status == DEAD)
			{
				currentTarget = NULL;
				isTargetSearch = true;
				static_cast<Boss*>(own)->isAiming = false;
				static_cast<Boss*>(own)->aimingTime = 0;
			}
		}

		if (!own->isExist)
			isExist = false;

		if (own->status == WOUNDED && status != WOUNDED)
		{
			status = WOUNDED;
			anim.setFrames(0, 128, 128, 128, 1, 1);
			anim.sound.setPitch(0.5f);
		}

		if (own->status == DEAD && status != DEAD)
			status = DEAD;

		if (status == DEAD)
		{
			if (isTransition)
			{
				if (anim.isEnd(time))
				{
					anim.frames[0] = IntRect(0, 384, 128, 128);
					anim.sound.stop();
					isDestroyed = true;
				}
				else
				{
					dir++;
					x += 0.4;
					y -= 0.4;
				}
			}
			else
			{
				name = "destroyed";
				isPlayAnimation = true;
				anim.setFrames(0, 256, 128, 128, 11, 0.008);
				isTransition = true;
			}
		}
	}
}

void TankTower::detectTarget(vector<Player*> &players, int currentTime)
{
	CircleShape aura = CircleShape(550.f);
	aura.setOrigin(aura.getGlobalBounds().width / 2, aura.getGlobalBounds().height / 2);
	aura.setPosition(x, y);
	FloatRect bossAura = aura.getGlobalBounds();

	for (int i = 0; i < players.size(); i++)
	{
		if (players[i]->status != DEAD)
		{
			double tX = (players[i]->dir == 0 || players[i]->dir == 180) ? players[i]->getCoordX(false) - 19 : players[i]->getCoordX(false) - 25;
			double tY = (players[i]->dir == 0 || players[i]->dir == 180) ? players[i]->getCoordY(false) - 25 : players[i]->getCoordY(false) - 19;

			FloatRect player = players[i]->dir == 0 || players[i]->dir == 180 ?
				FloatRect(tX, tY, 37, 49) : FloatRect(tX, tY, 49, 37);

			if (bossAura.intersects(player))
			{
				currentTarget = players[i];
				isTargetSearch = false;

				static_cast<Boss*>(own)->aimingTime = currentTime + 12;
				mortarShootTime = currentTime + 16;
				break;
			}
		}
	}
}

int TankTower::takeAim(GroundVehicle *player)
{
	double value = (y - player->getCoordY(false)) / (x - player->getCoordX(false));
	int angle = atan(value) * 180 / 3.14;

	if (x < player->getCoordX(false)) angle += 90;
	if (x > player->getCoordX(false)) angle += 270;

	if (x == player->getCoordX(false) && y > player->getCoordY(false)) angle = 0;
	if (x == player->getCoordX(false) && y < player->getCoordY(false)) angle = 180;
	if (y == player->getCoordY(false) && x > player->getCoordX(false)) angle = 270;

	return angle;
}
 
void TankTower::getRotationDirection(int &d, int &a) //.:: d - dir, a - angle
{
	int value = d > a ? d - a : a - d;

	(d > a && value < 180) ? d-- : (d > a && value > 180) ? d++ : d < a && value < 180 ? d++ : d--;
	resetDegrees(d);
}

void TankTower::destroyPlayerWithCannons()
{
	if (dir == 0 || dir == 90 || dir == 180 || dir == 270)
	{
		isFirstShot ? roundFirst = true : roundFirst = false;
		isSecondShot ? roundSecond = true : roundSecond = false;
	}
}

void TankTower::setNextAimingTime(int currentTime)
{
	static_cast<Boss*>(own)->isAiming = false;
	static_cast<Boss*>(own)->aimingTime = currentTime + 12;
	
	isMortarShootTime = false;
	mortarShootTime = currentTime + 16;
}

Tank* TankTower::getTargetForMortar(vector<Player*> players)
{
	int index;
	int counter = 0;
	while (true)
	{
		++counter;
		if (counter == 50) return NULL;

		index = rand() % players.size();
		if (players[index]->status != Status::DEAD)
			return players[index];
	}
}
