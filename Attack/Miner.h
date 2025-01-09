#pragma once

#include "GroundVehicle.h"

class Miner : public GroundVehicle
{
public:
	bool isStopped;

	//.:: Constructor :::::::::::::::::::::::
	Miner();
	Miner(Animation&, double, double, string, int, bool, SoundBuffer&, int, string, int, int);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Miner();

	//.:: Methods_of_class  :::::::::::::::::
	void update(double);
	bool isInOpenArea(string*);
	void rescheduleMining(int);

};
