#pragma once

#include "Animation.h"

Animation::Animation() {}

Animation::Animation(Texture& t, int x, int y, int width, int height, double animSpeed, int count)
{
	frame = 0;
	speed = animSpeed;

	setFrames(x, y, width, height, count, speed);

	sprite.setTexture(t);
	sprite.setOrigin(width / 2, height / 2);
	sprite.setTextureRect(frames[0]);
}

Animation::Animation(Texture& t, SoundBuffer& b, int x, int y, int width, int height, double animSpeed, int count)
{
	frame = 0;
	speed = animSpeed;

	setFrames(x, y, width, height, count, speed);

	sprite.setTexture(t);
	sprite.setOrigin(width / 2, height / 2);
	sprite.setTextureRect(IntRect(frames[0]));

	sound.setBuffer(b);
	sound.setLoop(true);
	sound.setPitch(0.9f);
	sound.setVolume(40.f);
}

Animation::~Animation() {}

void Animation::update(double time, bool on, int dir)
{
	sprite.setRotation(dir);
	int frameCount = frames.size();

	sound.pause();

	if (on)
	{
		sound.play();
		frame += speed * time;
		if (frame >= frameCount)
			frame -= frameCount;
	}
	if (frameCount > 0)
		sprite.setTextureRect(frames[(int)frame]);
}

bool Animation::isEnd(double time)
{
	return frame + speed * time >= frames.size();
}

FloatRect Animation::getRect(int dir)
{
	FloatRect rect = sprite.getGlobalBounds();
	switch (dir)
	{
	case 0: return FloatRect(rect.left, rect.top, 39, 52);
	case 90: return FloatRect(rect.left, rect.top, 52, 39);
	case 180: return FloatRect(rect.left, rect.top, 39, 52);
	case 270: return FloatRect(rect.left, rect.top, 52, 39);
	default: return rect;
	}
}

FloatRect Animation::getShellRect(bool isShell)
{
	FloatRect rect = sprite.getGlobalBounds();

	if (isShell)
		return FloatRect(rect.left, rect.top, 8, 8);
	else
		return FloatRect(rect.left, rect.top, 27, 27);
}

void Animation::setFrames(int x, int y, int width, int height, int count, double speed_)
{
	if (frames.size() > 0)
	{
		frames.clear();
		frame = 0;
	}

	for (int i = 0; i < count; i++)
		frames.push_back(IntRect((x + i * width), y, width, height));

	speed = speed_;
}

bool Animation::getPenultimateFrame(double time)
{
	return frame + speed * time == frames.size() - 2;
}
