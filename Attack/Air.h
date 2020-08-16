#pragma once

#include "Entity.h"

class Air : public Entity
{
private:
	Animation animSpare;
	Entity *own;
public:
	//.:: Constructors :::::::::::::::::::::
	Air();
	Air(Animation&, Animation&, Entity*, string);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~Air();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);
	Entity* getOwn();
};