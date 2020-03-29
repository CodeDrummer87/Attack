#pragma once

#include "Animation.h"

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

using namespace sf;

Animation::Animation() {}

Animation::Animation(Texture &t, SoundBuffer &b , int x, int y, int width, int height, double animSpeed, int count)
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
			//---------------------------------
			toUp.push_back(IntRect(x, y + height * i, width, height));
			toRight.push_back(IntRect(x + width, y + height * i, width, height));
			toDown.push_back(IntRect(x, y + height * i + height, width, -height));
			toLeft.push_back(IntRect(x + width * 2, y + height * i, -width, height));
		}
	}
	sprite.setTexture(t);
	sprite.setOrigin(width / 2, height / 2);
	sprite.setTextureRect(IntRect(frames[0]));

	sound.setBuffer(b);
	sound.setLoop(true);
	sound.setPitch(0.9f);
	sound.setVolume(30.f);
}

Animation::~Animation() {}

void Animation::update(double time, bool on, int dir)
{
	int frameCount;
	vector<IntRect> tempFrames;

	switch (dir)
	{
	case 0:
		tempFrames = frames;
		break;

	case 1:
		tempFrames = toUp;
		break;

	case 2:
		tempFrames = toRight;
		break;

	case 3:
		tempFrames = toDown;
		break;

	case 4:
		tempFrames = toLeft;
		break;
	}

	frameCount = tempFrames.size();

	sound.pause();

	if (on)
	{
		sound.play();
		frame += speed * time;
		if (frame >= frameCount)
			frame -= frameCount;
	}
	if (frameCount > 0)
		sprite.setTextureRect(tempFrames[(int)frame]);
}