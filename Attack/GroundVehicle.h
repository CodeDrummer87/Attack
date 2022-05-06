#pragma once

#include "Entity.h"
#include "Area.h"

struct Ban
{
	bool dir;	//.:: Direction is opened / closed
	int barId;	//.:: Barrier ID (if Direction is closed)
};

struct Traffic
{
	Ban up;
	Ban right;
	Ban down;
	Ban left;
};

class GroundVehicle : public Entity
{
private:
	float vehicleSpeed;
	float reachdDist;
	float destinationDist;

protected:
	bool isPlayerControl;
	bool isDestroyed;
	Animation aVehicleExplosion;

	bool isTransition;
	double toUp, toRight, toDown, toLeft;

	static int counter;

public:
	int number;
	int hitPoints;
	bool isSmoking;
	Traffic traffic;

	bool isShowRepair;

	//.:: Constructor :::::::::::::::::::::::
	GroundVehicle();
	GroundVehicle(Animation&, double, double, string, int, bool, Animation&, string, int);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~GroundVehicle();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);
	void accelerate(int, double);
	bool makeSureDestroyed();
	void checkVehiclesCollision(GroundVehicle*);
	bool makeSureVehicleCollision(GroundVehicle*);
	void getAreaDamage(Area*, string*);
	void checkMapCollision(string*);
	void checkIconCollision(string[], Sound&);
	void updateDestinationDistance();
	void controlEnemyVehicle(double);
	void changeDir();

};
