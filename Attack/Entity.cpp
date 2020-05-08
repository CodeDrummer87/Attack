#pragma once

#include "Entity.h"
#include "Animation.h"

#include <SFML\Graphics.hpp>
#include "Shell.h"

#include "Enemy.h"

using namespace sf;

int Entity::counter = 0;

Entity::Entity() {}

Entity::Entity(Animation &a, Entity *tank, string name_)
{
	anim = a;
	hitPoints = level = 0;

	if (name_ == "smoke")
	{
		dir = 1;
		x = tank->x;
		y = tank->y;
		playAnimation = true;
		if (tank->status == DEAD) level = 1;
		else level = 0;
	}
	if (name_ == "explosion" || name_ == "drowning")
	{
		dir = tank->dir;
		if (name_ == "explosion")
		{
			x = tank->getCoordX(true);
			y = tank->getCoordY(true);
		}
		else
		{
			x = tank->getCoordX(false);
			y = tank->getCoordY(false);
			anim.sprite.setColor(Color::Cyan);
		}
		playAnimation = true;

		if (tank->army != "player")
		{
			float result = 100 - (abs(y - getViewCoordY()) / 10);
			if (result > 50)
				result = 50.F;
			else if (result < 0)
				result = 0.F;

			anim.sound.setVolume(result);
		}
		else
			anim.sound.setVolume(50.f);
	}
	if (name_ == "rank")
	{
		dir = 1;
		x = tank->x + 32;
		y = tank->y - 32;
		playAnimation = false;
		anim.sprite.setScale(0.9f, 0.9f);
	}
	
	name = name_;
	own = tank;
	anim.sprite.setPosition(x, y);
	isExist = true;
	status = ALIVE;
}

Entity::~Entity() {}

void Entity::update(double time)
{
	if (isExist)
	{
		if (name == "explosion")
			if (anim.isEnd(time))
				isExist = false;

		if (name == "drowning")
			if (anim.isEnd(time))
			{
				if (own->army == "enemy")
					own->isExist = false;
				isExist = false;
			}


		if (name == "smoke")
		{
			if (static_cast<Tank*>(own)->isDrowned && !static_cast<Tank*>(own)->isTowed)
				isExist = false;

			x = own->x;
			y = own->y;

			if (level == 0)
			{
				if (own->status != WOUNDED)
				{
					if (own->name == "tank")
						static_cast<Tank*>(own)->isSmoking = false;
					isExist = false;
				}
			}
		}

		if (name == "rank")
		{
			if (own->level >= 6)
				anim.sprite.setScale(0.6f, 0.6f);

			if (own->level <= 19)
				anim.frame = float(own->level - 2);
			else
				anim.frame = 17;
			x = own->x + 32;
			y = own->y - 32;
			if (own->status == DEAD)
				isExist = false;
		}
	}
}

void Entity::collideEntities(Entity *e)
{
	if (anim.getRect(dir).intersects(e->anim.getRect(e->dir)))
	{
		switch (dir)
		{
		case 1:
			if (army == "player" && dy != 0 || army == "enemy")
			{
				if (traffic.up.barId == 0 && checkBarrierId(1, e->tokenId))
				{
					if (e->name != "destroyed")
					{
						if (e->dir == 1 && e->y > y)
						{
							traffic.down.dir = false;
							traffic.down.barId = e->tokenId;
						}
						else if (e->dir == 4 && e->x > x)
						{
							e->traffic.left.dir = false;
							e->traffic.left.barId = tokenId;
						}
						else
						{
							traffic.up.dir = false;
							traffic.up.barId = e->tokenId;
						}

						if (e->dy == 0)
						{
							e->traffic.down.dir = false;
							e->traffic.down.barId = tokenId;
						}
					}
				}

				//.:: Push the burning skeleton :::
				if (name == "tank" && e->name == "destroyed" && y > e->y && x > e->x - 20 && x < e->x + 20)
				{
					traffic.up.dir = e->traffic.up.dir = true;
					traffic.up.barId = e->tokenId;
					static_cast<Tank*>(e)->isTowed = true;
					dy /= 2;
					if (e->dir != 2)
						e->y = y - 52;
					else
						e->y = y - 40;
				}
			}
			break;

		case 2:
			if (army == "player" && dx != 0 || army == "enemy")
			{
				if (traffic.right.barId == 0 && checkBarrierId(2, e->tokenId))
				{
					if (e->name != "destroyed")
					{
						if (e->dir == 2 && e->x < x)
						{
							traffic.left.dir = false;
							traffic.left.barId = e->tokenId;
						}
						else
						{
							traffic.right.dir = false;
							traffic.right.barId = e->tokenId;
						}

						if (e->dx == 0)
						{
							e->traffic.left.dir = false;
							e->traffic.left.barId = tokenId;
						}
					}
				}

				//.:: Push the burning skeleton :::
				if (name == "tank" && e->name == "destroyed" && x < e->x && y > e->y - 20 && y < e->y + 20)
				{
					traffic.right.dir = e->traffic.right.dir = true;
					traffic.right.barId = e->tokenId;
					static_cast<Tank*>(e)->isTowed = true;
					dx /= 2;
					e->x = x + 52;
				}
			}
			break;

		case 3:
			if (army == "player" && dy != 0 || army == "enemy")
			{
				if (traffic.down.barId == 0 && checkBarrierId(3, e->tokenId))
				{
					if (e->name != "destroyed")
					{
						if (e->dir == 3 && e->y < y)
						{
							traffic.up.dir = false;
							traffic.up.barId = e->tokenId;
						}
						else
						{
							traffic.down.dir = false;
							traffic.down.barId = e->tokenId;
						}

						if (e->dy == 0)
						{
							e->traffic.up.dir = false;
							e->traffic.up.barId = tokenId;
						}
					}
				}

				//.:: Push the burning skeleton :::
				if (name == "tank" && e->name == "destroyed" && y < e->y && x > e->x - 20 && x < e->x + 20)
				{
					traffic.down.dir = e->traffic.down.dir = true;
					traffic.down.barId = e->tokenId;
					static_cast<Tank*>(e)->isTowed = true;
					dy /= 2;
					e->y = y + 52;
				}
			}
			break;

		case 4:
			if (army == "player" && dx != 0 || army == "enemy")
			{
				if (traffic.left.barId == 0 && checkBarrierId(4, e->tokenId))
				{
					if (e->name != "destroyed")
					{
						if (e->dir == 4 && e->x > x)
						{
							traffic.right.dir = false;
							traffic.right.barId = e->tokenId;
						}
						else
						{
							traffic.left.dir = false;
							traffic.left.barId = e->tokenId;
						}

						if (e->dx == 0)
						{
							e->traffic.right.dir = false;
							e->traffic.right.barId = tokenId;
						}
					}
				}

				//.:: Push the burning skeleton :::
				if (name == "tank" && e->name == "destroyed" && x > e->x && y > e->y - 20 && y < e->y + 20)
				{
					traffic.left.dir = e->traffic.left.dir = true;
					traffic.left.barId = e->tokenId;
					static_cast<Tank*>(e)->isTowed = true;
					dx /= 2;
					if (e->dir != 4 && e->dir != 1)
						e->x = x - 52;
					else
						e->x = x - 40;
				}
			}
			break;
		}
	}
	else
	{
		//.:: End of towning ::::
		if (traffic.up.barId == e->tokenId && static_cast<Tank*>(e)->isTowed)
		{
			traffic.up.barId = 0;
			static_cast<Tank*>(e)->isTowed = false;
		}

		if (traffic.right.barId == e->tokenId && static_cast<Tank*>(e)->isTowed)
		{
			traffic.right.barId = 0;
			static_cast<Tank*>(e)->isTowed = false;
		}

		if (traffic.down.barId == e->tokenId && static_cast<Tank*>(e)->isTowed)
		{
			traffic.down.barId = 0;
			static_cast<Tank*>(e)->isTowed = false;
		}

		if (traffic.left.barId == e->tokenId && static_cast<Tank*>(e)->isTowed)
		{
			traffic.left.barId = 0;
			static_cast<Tank*>(e)->isTowed = false;
		}
		//:::::::::::::::::::::::

		if (!traffic.right.dir)
		{		
			if (traffic.right.barId == e->tokenId)
			{
				traffic.right.barId = 0;	traffic.right.dir = true;
			}
		}

		if (!traffic.left.dir)
		{
			if (traffic.left.barId == e->tokenId)
			{
				traffic.left.barId = 0;		traffic.left.dir = true;
			}
		}

		if (!traffic.up.dir)
		{
			if (traffic.up.barId == e->tokenId)
			{
				traffic.up.barId = 0;	traffic.up.dir = true;
			}
		}

		if (!traffic.down.dir)
		{
			if (traffic.down.barId == e->tokenId)
			{
				traffic.down.barId = 0;	traffic.down.dir = true;
			}
		}
	}

	//.:: Enemy tanks conduct targeted fire :::
	if (name == "tank" && army == "enemy" && e->name == "tank" && e->army == "player")
	{
		switch (dir)
		{
		case 1:
			if (y > e->y)
				if (x >= e->x - 32 && x <= e->x + 32 && y - e->y <= 400)
					if (this->checkObstacles(FirstStage, 'B'))
						if (!static_cast<Enemy*>(this)->round)
							static_cast<Enemy*>(this)->round = true;
			break;

		case 2:
			if (x < e->x)
				if (y >= e->y - 32 && y <= e->y + 32 && e->x - x <= 400)
					if (this->checkObstacles(FirstStage, 'B'))
						if (!static_cast<Enemy*>(this)->round)
							static_cast<Enemy*>(this)->round = true;
			break;

		case 3:
			if (y < e->y)
				if (x >= e->x - 32 && x <= e->x + 32 && e->y - y <= 400)
					if (this->checkObstacles(FirstStage, 'B'))
						if (!static_cast<Enemy*>(this)->round)
							static_cast<Enemy*>(this)->round = true;
			break;

		case 4:
			if (x > e->x)
				if (y >= e->y - 32 && y <= e->y + 32 && x - e->x <= 400)
					if (this->checkObstacles(FirstStage, 'B'))
						if (!static_cast<Enemy*>(this)->round)
							static_cast<Enemy*>(this)->round = true;
			break;
		}
	}
}

/// The method exists to protect against repeated intersection
/// with an already intersecting object.
/// Checking goes in all directions except one (first parameter)
bool Entity::checkBarrierId(int dir_, int id)
{
	bool check = true;

	switch (dir_)
	{
	case 1: 
		if (traffic.left.barId == id || traffic.down.barId == id || traffic.right.barId == id)
			check = false;
		break;

	case 2:
		if (traffic.up.barId == id || traffic.down.barId == id || traffic.left.barId == id)
			check = false;
		break;

	case 3:
		if (traffic.up.barId == id || traffic.left.barId == id || traffic.right.barId == id)
			check = false;
		break;

	case 4:
		if (traffic.up.barId == id || traffic.down.barId == id || traffic.right.barId == id)
			check = false;
		break;
	}

	return check;
}

double Entity::getCoordX(bool isShell)
{
	double xCoordinate = x;

	if (isShell)
	{
		switch (dir)
		{
		case 1: xCoordinate; break;
		case 2: xCoordinate += 42; break;
		case 3: xCoordinate; break;
		case 4: xCoordinate -= 42; break;
		}
	}

	return xCoordinate;
}

double Entity::getCoordY(bool isShell)
{
	double yCoordinate = y;

	if (isShell)
	{
		switch (dir)
		{
		case 1: yCoordinate -= 42; break;
		case 2: yCoordinate; break;
		case 3: yCoordinate += 42; break;
		case 4: yCoordinate; break;
		}
	}

	return yCoordinate;
}

void Entity::damageEntity(Entity *e, Sound &armorSound)
{
	if (army != e->army)
		if (anim.getShellRect(true).intersects(e->anim.getShellRect(false)))
		{
			armorSound.play();
			if (this->name == "shell" && e->name == "tank")
			{
				if (level >= e->hitPoints && e->hitPoints > 1)
					e->hitPoints = 1;
				else
					e->hitPoints -= level;
				if (army == "player" && e->hitPoints <= 0)
					static_cast<Shell*>(this)->conveyExperience(e->level);
				if (army == "enemy" && e->hitPoints <= 0)
					static_cast<Shell*>(this)->ceaseEnemyFire();
			}
			isExist = false;
			if (name == "shell")
				static_cast<Shell*>(this)->allowShot();
		}
}

void Entity::draw(RenderWindow &app)
{
	anim.sprite.setPosition(x, y);
	app.draw(anim.sprite);
}

void Entity::getCollision(String map[], Sound &sound)
{
	if (name != "explosion")
		if (name == "shell")
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
						static_cast<Shell*>(this)->explosion = true;
						if (map[i][j] == 'b')
							map[i][j] = ' ';
					}

					if (map[neighborCoordY][neighborCoordX] == 'b')
					{
						static_cast<Shell*>(this)->explosion = true;
						map[neighborCoordY][neighborCoordX] = ' ';
					}	
				}
		}
		else
		{
			for (int i = (anim.getRect(dir).top + 15) / 32; i < (y + anim.getRect(dir).height) / 32; i++)
				for (int j = (anim.getRect(dir).left + 14) / 32; j < (x + anim.getRect(dir).width) / 32; j++)
				{
					//.:: Enemy tanks destroy brick walls :::
					if (name == "tank" && army == "enemy" && !this->checkObstacles(map, 'b'))
					{
						if (!static_cast<Enemy*>(this)->round)
							static_cast<Enemy*>(this)->round = true;
					}

					if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W' && name != "destroyed")
					{
						if (name == "tank")
						{
							if (i * 32 < y && j * 32 > x - 26 && j * 32 < x + 26)
							{
								if (dy < 0)
									dy += 0.2F;
								if (army == "enemy")
									dy += 0.2F;
							}
					
							if (i * 32 > y && j * 32 > x - 26 && j * 32 < x + 26)
							{
								if (dy > 0)
									dy -= 0.2F;
								if (army == "enemy")
									dy -= 0.2F;
							}

							if (j * 32 > x && i * 32 > y - 26 && i * 32 < y + 26)
							{
								if (dx > 0)
									dx -= 0.2F;
								if (army == "enemy")
									dx -= 0.2F;
							}

							if (j * 32 < x && i * 32 > y - 26 && i * 32 < y + 26)
							{
								if (dx < 0)
									dx += 0.2F;
								if (army == "enemy")
									dx += 0.2F;
							}

							if (army == "enemy")
								static_cast<Enemy*>(this)->changeDir();
						}
					}

					if (map[i][j] == 'U' && name == "tank")
					{
						if (army == "player")
						{
							sound.play();
							static_cast<Player*>(this)->preferment = true;
							map[i][j] = ' ';
						}
					}

					if (map[i][j] == 'R' && name == "tank")
					{
						if (hitPoints < 1 + level)
						{
							sound.play();
							++hitPoints;
							map[i][j] = ' ';
						}
					}

					if (map[i][j] == 'C' && name == "tank" && army == "player")
					{
						sound.play();
						map[i][j] = ' ';
						static_cast<Player*>(this)->isCommander = true;
					}

					if (name == "destroyed")
						if (map[i][j] == 'W' && !static_cast<Tank*>(this)->isTowed)
						{
							anim.sprite.setColor(Color::Transparent);
							if (!static_cast<Tank*>(this)->isDrowned)
								static_cast<Tank*>(this)->isDrowned = true;
						}
				}
		}
}

bool Entity::checkObstacles(String map[], char ch)
{
	int i = y / 32;
	int iStart = i;

	int j = x / 32;
	int jStart = j;

	int subtrahend = 12;

	switch (dir)
	{
	case 1:
		if (iStart - 12 < 0)
			subtrahend = iStart;

		for (; i > iStart - subtrahend; i--)
		{
			if (map[i][j] == ch)
				return false;

			if (ch == 'b')
				if (map[i][j] == 'B')
					return true;
		}
		break;

	case 2:
		if (jStart + 12 > 34)
			subtrahend = 34 - jStart;

		for (; j < jStart + subtrahend; j++)
		{
			if (map[i][j] == ch)
				return false;
		
			if (ch == 'b')
				if (map[i][j] == 'B')
					return true;
		}
		break;

	case 3:
		if (iStart + 12 > 61)
			subtrahend = 61 - iStart;

		for (; i < iStart + subtrahend; i++)
		{
			if (map[i][j] == ch)
				return false;

			if (ch == 'b')
				if (map[i][j] == 'B')
					return true;
		}
		break;

	case 4:
		if (jStart - 12 < 0)
			subtrahend = jStart;

		for (; j > jStart - subtrahend; j--)
		{
			if (map[i][j] == ch)
				return false;

			if (ch == 'b')
				if (map[i][j] == 'B')
					return true;
		}
		break;
	}

	return true;
}

extern View view;

float Entity::getViewCoordY()
{
	return view.getCenter().y;
}