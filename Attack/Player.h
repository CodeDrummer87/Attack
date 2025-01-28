#pragma once

#include "Tank.h"

struct Tuple
{
	double x;
	double y;
};

struct PlayersPositions
{
	Tuple first{ 0, 0 };
	Tuple second{ 0, 0 };
	Tuple third{ 0, 0 };
	Tuple fourth{ 0, 0 };
	Tuple fifth{ 0, 0 };
};

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

	Animation moveAnim;

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

	bool isPartisan;
	bool isDisplayPartisanAchievement;
	int partisanAchievLevel;
	int killsInForest;

	short lives;
	bool willRessurect;
	int ressurectionTime;
	Tuple startPosition;

	//.:: Constructor ::::::::::::::::::::::
	Player();
	Player(Animation&, double, double, SoundBuffer&, int);

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
	static Player* getCommander(vector<Player*>);
	void insertCodeSymbol(char);
	bool checkCollisionWithDestroyedTank(GroundVehicle*);
	void setTow(GroundVehicle*, string);
	void towBack(double);
	void checkMapCollisionWhenTow(string *);
	void controlOfTank(char, double, double);
	void countKillsInForest();
	int activateGuerillaMode();
	void prepareForRessurection();
	void ressurectPlayer();
	void ressurectPlayer(double, double);
	bool willFight();

};
