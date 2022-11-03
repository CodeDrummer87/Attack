#pragma once

#include "Tank.h"

struct AirSpotter
{
	bool isAirSpotter;
	Entity *currentPlayer;
	bool isTargetCreated;
	double xTargetPosition;
	double yTargetPosition;
};

class Player : public Tank
{
private:
	int totalKills;
	int currentExperience;
	int requiredExperience;

	//.:: Methods_of_class :::::::::::::::::
	bool checkTowingDirectionBan(char);

public:
	bool hasRank;
	bool isPreferment;
	bool isCommander;

	static AirSpotter airSpotter;

	bool isTowingBack;
	bool isKeyPressed;
	char combo[4];
	string currentCipher;
	GroundVehicle * destroyedVehicle;

	//.:: Constructor ::::::::::::::::::::::
	Player();
	Player(Animation&, double, double, string, int, bool, SoundBuffer&, int, string, int);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~Player();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);
	void setStartPosition(double, double);
	void checkIconCollision(string[], int, Sound&);
	void improveTank(int);
	void nickDown(int);
	
	static void defineNewCommander(vector<Player*>&);
	static bool checkTeamForCommander(vector<Player*>);
	void insertCodeSymbol(char);
	bool checkCollisionWithDestroyedTank(GroundVehicle*);
	void setTow(GroundVehicle*, string);
	void towBack(double);
	void checkMapCollisionWhenTow(string *);
	void controlOfTank(char, double, double);

};
