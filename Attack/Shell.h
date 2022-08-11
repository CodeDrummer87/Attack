#pragma once

#include "Tank.h"

class Shell : public Entity
{
private:
	float dist;
	Animation aExplosion;
	Tank *own;

	//.:: Private_methods_of_class ::::::::::
	void conveyExperience(int);
	void paintOwn();

public:
	bool isExplosion;

	//.:: Constructor :::::::::::::::::::::::
	Shell();
	Shell(Animation&, Animation&, Tank*);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Shell();

	//.:: Public_methods_of_class :::::::::::
	void update(double);
	void checkMapCollision(string[]);
	void damageVehicle(GroundVehicle*, Sound&);
	void damageBoss(GroundVehicle*, Sound&, Sound&);
	int getCounterDirection(int);

};

