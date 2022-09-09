#pragma once

#include "GroundVehicle.h"

enum Camera { NotDefined, StartGame, Commander, MalevolentTank, Target, FirstPlane, StartGameSetted };

class Tank : public GroundVehicle
{
public:
	bool isShot;
	int drownedTanks;

	bool isSpeedBonusUp;
	bool isShowSpeedBonusAchiev;

	short destValue;
	float shellSpeedBonus;	//.:: Achievement "Sniper": Shell speed boost bonus
	bool isShowSniperAchiev;

	static Camera camera;

	//.:: Constructor :::::::::::::::::::::::
	Tank();
	Tank(Animation&, double, double, string, int, bool, SoundBuffer&, int, string, int);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Tank();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);
	void shoveOffTankCarcass(GroundVehicle*);

};
