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
	bool isIconTaken;

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
	Player(Animation&, double, double, int, bool, SoundBuffer&, int, int);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~Player();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);
	void setStartPosition(double, double);
	void checkIconCollision(Entity*, Sound&);
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
