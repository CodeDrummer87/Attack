#pragma once

#include "Entity.h"
#include "Player.h"

class Shell : public Entity
{
private:
	float dist;		// The way done
	Animation animSpare;
	Tank *own;

public:
	bool explosion;

	//.:: Constructors :::::::::::::::::::::
	Shell();
	Shell(Animation&, Animation&, Tank*);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~Shell();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);
	void allowShot();
	void conveyExperience(int);
	void ceaseEnemyFire();
	void paintOwn();
};