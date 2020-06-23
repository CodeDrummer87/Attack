#pragma once

#include "Entity.h"

class Air : public Entity
{
private:
	Entity *attachedObject;
public:
	//.:: Constructors :::::::::::::::::::::
	Air();
	Air(Animation&, int, int, int, string, Entity*);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~Air();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);
};