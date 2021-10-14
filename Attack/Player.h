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

public:
	bool hasRank;
	bool isPreferment;
	bool isCommander;

	static AirSpotter airSpotter;

	//.:: Constructor ::::::::::::::::::::::
	Player();
	Player(Animation&, double, double, string, int, bool, Animation&, string, int);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~Player();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);
	void setStartPosition(double, double);
	void checkIconCollision(string[], Sound&);
	void improveTank(int);
	
	static void defineNewCommander(vector<Player*>);
	static bool checkTeamForCommander(vector<Player*>);

};
