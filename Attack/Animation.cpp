#pragma once

#include "Animation.h"
#include <SFML\Graphics.hpp>

using namespace sf;

Animation::Animation() {}

Animation::Animation(Texture &t, int x, int y, int width, int height, float animSpeed, int count)
{
	frame = 0;
	speed = animSpeed;
	if (count > 2)
		for (int i = 0; i < count; i++)
			frames.push_back(IntRect(x + width * i, y, width, height));
	else
	{
		for (int i = 0; i < count; i++)
		{	
			frames.push_back(IntRect(x, y + height * i, width, height));
		}
	}
	sprite.setTexture(t);
	sprite.setOrigin(width / 2, height / 2);
	sprite.setTextureRect(IntRect(frames[0]));
}

Animation::~Animation() {}

void Animation::update(double time, bool on)
{
	int frameCount;
	frameCount = frames.size();
	if (on)
	{
		frame += speed * time;		
		if (frame >= frameCount)
			frame -= frameCount;
	}
	if (frameCount > 0)
		sprite.setTextureRect(frames[(int)frame]);

}