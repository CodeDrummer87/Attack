#include "Entity.h"

Entity::Entity()
{}

Entity::Entity(Animation &a, double x_, double y_, string name_, int dir_, bool isPlayAnimation_)
{
	anim = a;
	x = x_;
	y = y_;
	name = name_;
	dir = dir_;
	isPlayAnimation = isPlayAnimation_;

	isExist = true;
}

Entity::~Entity()
{}

void Entity::update(double time)
{}

void Entity::draw(RenderWindow &app)
{
	anim.sprite.setPosition(x, y);
	app.draw(anim.sprite);
}
