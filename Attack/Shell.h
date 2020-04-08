#pragma once

#include "Entity.h"
#include "Player.h"

class Shell : public Entity
{
private:
	float dist;		// The way done
	Animation animSpare;
	Player *own;

public:
	//.:: Constructors :::::::::::::::::::::
	Shell();
	Shell(Animation&, Animation&, Player*);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~Shell();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);
	void allowShot();
	void conveyExperience(int);
};