#pragma once

#include "Entity.h"
#include "Animation.h"
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

Entity::Entity() {}

Entity::~Entity() {}

void Entity::setEntity(Animation &a, int X, int Y)
{
	anim = a;
	x = X;
	y = Y;
	anim.sprite.setPosition(x, y);
	playAnimation = false;
}

void Entity::update(double time) {}

void Entity::draw(RenderWindow &app)
{
	anim.sprite.setPosition(x, y);
	app.draw(anim.sprite);
}
