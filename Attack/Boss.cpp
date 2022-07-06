#include "Boss.h"

Boss::Boss()
{}

Boss::Boss(BossArgs &args)
	: Enemy(args.anim, args.x, args.y, args.name, args.dir, args.isPlayAnimation, args.aExplosion, "enemy", args.level)
{
	aTower = args.aTower;
	aTower.sprite.setPosition(x, y);
	aTowerCrash = args.aTowerCrash;

	hitPoints = 100 + args.numberOfPlayers * 25;

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

void Boss::checkMapCollision(string *map)
{
	if (dir == 1)
		for (int i = (y - 30) / 32; i <= (y + 40) / 32; i++)
			for (int j = (x - 2) / 32; j <= (x + 60) / 32; j++)
			{
				if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
					traffic.up.dir = false;

				if (!traffic.down.dir)
					traffic.down.dir = true;
			}

	if (dir == 3)
		for (int i = (y + 20) / 32; i <= (y + 60) / 32; i++)
			for (int j = (x - 4) / 32; j <= (x + 60) / 32; j++)
			{
				if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
					traffic.down.dir = false;

				if (!traffic.up.dir)
					traffic.up.dir = true;
			}

	if (dir == 4)
		for (int i = (y) / 32; i <= (y + 40) / 32; i++)
			for (int j = (x - 30) / 32; j <= (x + 20) / 32; j++)
			{
				if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
					traffic.left.dir = false;

				if (!traffic.right.dir)
					traffic.right.dir = true;
			}

	if (dir == 2)
		for (int i = (y-10) / 32; i <= (y + 40) / 32; i++)
			for (int j = (x + 52) / 32; j <= (x + 64) / 32; j++)// 42  50
			{
				if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
					traffic.right.dir = false;

				if (!traffic.left.dir)
					traffic.left.dir = true;
			}
}
