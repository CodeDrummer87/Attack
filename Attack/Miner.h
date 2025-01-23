#pragma once

#include "GroundVehicle.h"

class Miner : public GroundVehicle
{
public:
	bool isStopped;
	bool isInRadarCoverageArea;

	//.:: Constructor :::::::::::::::::::::::
	Miner();
	Miner(Animation&, double, double, SoundBuffer&, int);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Miner();

	//.:: Methods_of_class  :::::::::::::::::
	void update(double);
	bool isInOpenArea(string*);
	void rescheduleMining(int);

};
