#include "Area.h"

Area::Area()
{}

Area::Area(double X, double Y, float radius, Entity *own_, string name_)
{
	name = name_;
	x = X;
	y = Y;
	area = CircleShape(radius);
	area.setOrigin(area.getGlobalBounds().width / 2, area.getGlobalBounds().height / 2);
	area.setPosition(x, y);

	own = own_;
	army = own->army;
	isExist = true;

	status = ALIVE;
}

short Area::victims = 0;

Area::~Area()
{}

void Area::update(double time)
{
	if (status == WOUNDED)
		isExist = false;

	if (own->status == WOUNDED && !own-isExist)
		status = WOUNDED;
}
