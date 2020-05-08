#pragma once

#include <SFML\Graphics.hpp>
#include "Animation.h"

using namespace sf;

enum Status { DEAD, ALIVE, WOUNDED };

struct Ban
{
	bool dir;	//.:: Direction open / close
	int barId;	//.:: Barrier ID (if Direction is close)
};

struct Traffic
{
	Ban up;
	Ban right;
	Ban down;
	Ban left;
};

extern String FirstStage[];

class Entity
{
private:
	Entity *own;
protected:
	static int counter;
	double x, y, dx, dy;		// coordinates: x, y; acceleration x and y;
	double toUp, toRight, toDown, toLeft;
public:
	int tokenId;
	string name;
	string army;
	int dir;
	Animation anim;
	bool playAnimation;
	bool isExist;
	Status status;
	Traffic traffic;
	int hitPoints;
	int level;
	//.:: Constructors ::::::::::::::::::::::
	Entity();
	Entity(Animation&, Entity*, string);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Entity();

	//.:: Methods_of_class ::::::::::::::::::
	virtual void update(double);
	void collideEntities(Entity*);
	bool checkBarrierId(int, int);
	double getCoordX(bool);
	double getCoordY(bool);
	void damageEntity(Entity*, Sound&);
	void draw(RenderWindow&);
	void getCollision(String[], Sound&);
	bool checkObstacles(String[], char);
	float getViewCoordY();
};