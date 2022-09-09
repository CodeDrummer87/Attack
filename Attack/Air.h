#pragma once

#include "Entity.h"
#include "Player.h"

enum BombStatus { ABOARD, DROPPED, DESCENT };

class Air : public Entity
{
private:
	Animation animSpare;
	Entity *own;

public:
	//.:: Constructor ::::::::::::::::::::::
	Air();
	Air(Animation&, Animation&, Entity*, string);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~Air();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);
	Entity* getOwn();

};
