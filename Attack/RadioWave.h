#pragma once

#include "Air.h"
#include "RadioAntenna.h"

class RadioWave : public Air
{
private:
	RadioAntenna *antenna;

public:

	//.:: Constructor :::::::::::::::::::::::
	RadioWave();
	RadioWave(Animation&, RadioAntenna*, string);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~RadioWave();

	//.:: Methods_of_class  :::::::::::::::::
	void update(double);
};

