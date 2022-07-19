#include "Rank.h"

Rank::Rank()
{}

Rank::Rank(Animation &a, Tank *tank, string name_)
{
	z_index = 2;

	anim = a;
	level = 0;

	dir = 1;
	x = tank->getCoordX(false) + 32;
	y = tank->getCoordY(false) - 32;
	isPlayAnimation = false;
	anim.sprite.setScale(0.4f, 0.4f);

	name = name_;
	own = tank;
	anim.sprite.setPosition(x, y);
	isExist = true;
	status = ALIVE;
}

Rank::~Rank()
{}

void Rank::update(double time)
{
	if (isExist)
	{
		if (own->level >= 6 && own->level <= 9)
			anim.sprite.setScale(0.32f, 0.32f);
		else if (own->level >= 10)
			anim.sprite.setScale(0.25f, 0.25f);

		if (own->level <= 19)
			anim.frame = float(own->level - 2);
		else
			anim.frame = 17;
		x = own->getCoordX(false) + 32;
		y = own->getCoordY(false) - 32;
		if (own->name == "destroyed")
			isExist = false;
	}
}
