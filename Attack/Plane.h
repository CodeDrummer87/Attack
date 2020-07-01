#pragma once

#include "Air.h"

enum BombStatus { ABOARD, DROPPED, DESCENT };

struct Leading
{
	bool openPosition;
	Entity *plane;
};

class Plane : public Air
{
private:
	Animation aEssential;
	Animation aTrace;
	Animation aJetFlame;

	Entity *attachedObject;
public:
	BombStatus bombStatus;
	static Leading leader;

	//.:: Constructors ::::::::::::::::::::::
	Plane();
	Plane(Animation&, Animation&, Animation&, double, double, string, Entity*);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Plane();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);
	void draw(RenderWindow&);
};