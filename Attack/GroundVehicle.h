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
	bool areDirectionsOpen;
};

class GroundVehicle : public Entity
{
private:
	float vehicleSpeed;
	float reachDist;
	float destinationDist;

	bool isSkidding;
	int puddleId;
	
	//.:: Methods_of_class ::::::::::::::::::
	void resetSkidding(bool, int);

protected:
	float speedBonus;
	bool isPlayerControl;
	bool isDestroyed;
	SoundBuffer sExplosion;
	int explosionFrameCount;

	bool isTransition;
	double toUp, toRight, toDown, toLeft;

	static int counter;

public:
	int hitPoints;
	bool drowning;
	bool isSmoking;
	bool isDrowned;
	GroundVehicle *pusher;	//.:: Only tanks
	Traffic traffic;

	bool isShowRepair;

	//.:: Constructor :::::::::::::::::::::::
	GroundVehicle();
	GroundVehicle(Animation&, double, double, string, int, bool, SoundBuffer&, int, string, int);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~GroundVehicle();

	//.:: Methods_of_class ::::::::::::::::::
	virtual void checkMapCollision(string*);
	
	void update(double);
	void accelerate(int, double);
	bool makeSureDestroyed();
	void checkVehiclesCollision(GroundVehicle*);
	bool makeSureVehicleCollision(GroundVehicle*);
	void getAreaDamage(Area*, string*);
	void checkIconCollision(string[], Sound&);
	void updateDestinationDistance();
	void controlEnemyVehicle(double);
	void changeDir();
	void sinkTankCarcass(string*);
	void checkPuddlesCollision(Entity*);
	void checkBossCollision(GroundVehicle*, Sound&);

};