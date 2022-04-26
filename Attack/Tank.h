#pragma once

#include "GroundVehicle.h"

enum Camera { NotDefined, StartGame, Commander, MalevolentTank, Target, FirstPlane, StartGameSetted };

class Tank : public GroundVehicle
{
private:
	float speedBonus;	//.:: Achievement "Cleaner": Movement speed boost bonus
	bool isSpeedBonusUp;

protected:
	int drownedTanks;

public:
	bool isShot;
	bool isDrowned;
	bool drowning;

	bool isShowRepair;
	bool isShowSpeedBonusAchiev;

	short destValue;
	float shellSpeedBonus;	//.:: Achievement "Sniper": Shell speed boost bonus
	bool isShowSniperAchiev;
	Tank *pusher;

	static Camera camera;

	//.:: Constructor :::::::::::::::::::::::
	Tank();
	Tank(Animation&, double, double, string, int, bool, Animation&, string, int);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Tank();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);
	void accelerate(int, double);
	void shoveOffTankCarcass(Tank*);
	void sinkTheTankCarcass(string*);

};
