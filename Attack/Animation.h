#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

class Animation
{
public:
	float frame, speed;
	Sprite sprite;
	vector<IntRect> frames;
	//.:: Constructors ::::::::::::::::::::::
	Animation();
	Animation(Texture &t, int, int, int, int, float, int);	// texture, coordinates: x, y; width, height, animation_speed, frames_count
	
	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Animation();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);
};

