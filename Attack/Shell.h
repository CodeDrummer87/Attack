#pragma once

#include "Entity.h"
#include "Tank.h"

class Shell : public Entity
{
private:
	float dist;
	Animation aExplosion;
	Tank *own;

public:
	string army;
	bool isExplosion;

	//.:: Constructor :::::::::::::::::::::::
	Shell();
	Shell(Animation&, Animation&, Tank*);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Shell();

	//.:: Methods_of_update :::::::::::::::::
	void update(double);
	void checkMapCollision(string[]);

};

