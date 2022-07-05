#include "Boss.h"

Boss::Boss()
{}

Boss::Boss(BossArgs &args)
	: Enemy(args.anim, args.x, args.y, args.name, args.dir, args.isPlayAnimation, args.aExplosion, "enemy", args.level)
{
	aTower = args.aTower;
	aTower.sprite.setPosition(x, y);
	aTowerCrash = args.aTowerCrash;

	rot = 0;
}

Boss::~Boss()
{}

void Boss::update(double time)
{
	rot++;
	aTower.sprite.setRotation(rot);

	GroundVehicle::update(time);
}

void Boss::draw(RenderWindow &app)
{
	anim.sprite.setPosition(x, y);
	app.draw(anim.sprite);

	aTower.sprite.setPosition(x, y);
	app.draw(aTower.sprite);
}
