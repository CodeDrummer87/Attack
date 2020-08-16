#pragma once

#include <SFML\Graphics.hpp>

using namespace sf;

const int H = 68;
const int W = 61;

String FirstStage[H] = 
{
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
	"B                                                           B",
	"B                                                           B",
	"BFFFFFF      FFFFFF      FFFFFF      FFFFFF      FFFFFF     B",
	"BFFFFFF      FFFFFF      FFFFFF      FFFFFF      FFFFFF     B",
	"B                                                           B",
	"B                                                           B",
	"B                                                           B",
	"B                                                           B",
	"BFFFFF                      bbbbbbbbb                       B",
	"BFFFFF                      bbbbbbbbb                       B",
	"BFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBBBBBBB                       B",
	"BFFFFFFFFFFFFFFFFFFFFFFFFFFFBB     BB                       B",
	"BFFFFFFFFFFFFFFFFFFFFFFFFFFFBB  U  BBFFFFFFFFFFFFFFFFFFFFFFFB",
	"BBBBWWWWWWWWWWWWBBBBBBFFFFFFBB     BBFFFFFFFFFFFFFFFFFFFFFFFB",
	"BBBBWWWWWWWWWWWWBBBBBBFFFFFFBB     BB      A                B",
	"BBBBBBBBBBBBBBBBBBBBBBFFFFFFBB     BB                       B",
	"BBBBBBBBBBBBBBBBBBBBBBFFFFFFBB     BB      BBBBBBBB         B",
	"BBBBBBBBBBBBBBBBBBBBBBFFFFFFBB     BB      BBBBBBBB         B",
	"Bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb                       B",
	"B                                                           B",
	"B                                                           B",
	"B                                                           B",
	"B R                                                         B",
	"BFFFF                 BBBB         BBBB                     B",
	"BFFFFFFFF    bbbb     BBBB         BBBB                     B",
	"BFFFFFFFFFFFFbbbb     bbbb         bbbb                     B",
	"BFFFFFFFFFFFFbbbbFFFFFFFFFFFFFFFFFFFFFFFFFFbbbb      U      B",
	"BFFFFFFFFFFFFbbbbFFFFFFFFFFFFFFFFFFFFFFFFFFbbbb             B",
	"BFFFFFFFFFFFFWWWWWW   BBBB         BBBB                     B",
	"BFFFFFFFF    WWWWWW   BBBB    R    BBBB                  WWWB",
	"BFFFF                     BB     BB                      WWWB",
	"B                         BBBBBBBBBbbbbbbbbbbbbbbbbbWWWWWWWWB",
	"B     bbbbFFFFbbbbbbb     bbbbbbbbb                 WWWWWWWWB",
	"B     bbbbFFFFbbbbbbb      bbbbbbb                  FFFFFWWWB",
	"B     bbbb      WWWW        bbbbb                   FFFFFFFFB",
	"B     bbbb      WWWW         bbb                            B",
	"B     bbbb      WWWW          b       bbbbbbbbbbbbbb        B",
	"B     bbbb                            bbbbbbbbbbbbbb        B",
	"B     bbbb                                                  B",
	"B                                                           B",
	"B   BBBBBBBBBB     WWWWWWWWWWWWWWWWWWWWWWW     BBBBBBBBBB   B",
	"BbbbWWWWFFFFFF     WWWWWWWWWWWWWWWWWWWWWWW     FFFFFFWWWWbbbB",
	"BbbbWWWWFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFWWWWbbbB",
	"BbbbWWWWbbbbFFFFFF        bbbbbbb          FFFFFFbbbbWWWWbbbB",
	"BbbbWWWWbbbbFFFFFF   R    bbbUbbb    R     FFFFFFbbbbWWWWbbbB",
	"BbbbWWWWbbbWWWWWWWbb      bbbbbbb        bbWWWWWWWbbbWWWWbbbB",
	"BbbbWWWWbUbWWWWWWWbb      bbbbbbb        bbWWWWWWWbUbWWWWbbbB",
	"B                            B                              B",
	"B                           UBU                             B",
	"B            BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB             B",
	"B                                                           B",
	"B                 A          C     A                        B",
	"B                                                           B",
	"BWWWWWWWWWWWWWWWWWWWWWWWWWWFFFFFFWWWWWWWWWWWWWWWWWWWWWWWWWWWB",
	"BWWWWWWWWWWWWWWWWWWWWWWWWWWFFFFFFWWWWWWWWWWWWWWWWWWWWWWWWWWWB",
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBFFFFFFBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
	"BBBBBBBBBBBWWWWWWWWWWWWWWWWFFFFFFWWWWWWWWWWWWWWWWWBBBBBBBBBBB",
	"BBBBBBBBBBWWWWWWWWWWWWWWWWWFFFFFFWWWWWWWWWWWWWWWWWWBBBBBBBBBB",
	"BBBBBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBBBBBBB",
	"BBBBBBBBFFFFFFFFFbbbbbbbbbbbbbbbbbbbbbbbbbbbFFFFFFFFFBBBBBBBB",
	"BBBBBBBFFFFFFFFbbbbb                     bbbbbFFFFFFFFBBBBBBB",
	"BBBBBBFFFFFFFbbbbbbb                     bbbbbbbFFFFFFFBBBBBB",
	"BBBBBFFFFFFFbbbbbb                         bbbbbbFFFFFFFBBBBB",
	"BBBBFFFFFFFbbbbbbb                         bbbbbbbFFFFFFFBBBB",
	"BBBFFFFFFFbbbbbb                             bbbbbbFFFFFFFBBB",
	"BBFFFFFFFbbbbbbb                             bbbbbbbFFFFFFFBB",
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
};

RectangleShape rectangle(Vector2f(32, 32));

void drawMap(String map[H], RenderWindow &app, Animation &a, double time)
{
	a.update(time, true, 1);

	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
		{
			if (map[i][j] == 'W')
				a.sprite.setTextureRect(a.frames[(int)a.frame]);
			else if (map[i][j] == 'B')
				a.sprite.setTextureRect(IntRect(0, 32, 32, 32));
			else if (map[i][j] == 'b')
				a.sprite.setTextureRect(IntRect(96, 32, 32, 32));
			else
				continue;

			a.sprite.setPosition(float(j * 32), float(i * 32));
			app.draw(a.sprite);
		}
}

void drawForestAndIcons(String map[H], RenderWindow &app, Animation &a, Animation icons[], double time)
{
	for (int i = 0; i < sizeof(icons); i++)
		icons[i].update(time, true, 1);

	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
		{
			if (map[i][j] == 'F')
			{
				a.sprite.setTextureRect(IntRect(32, 32, 32, 32));
				a.sprite.setPosition(float(j * 32), float(i * 32));
				app.draw(a.sprite);
			}

			if (map[i][j] == 'R')
			{
				icons[0].sprite.setTextureRect(icons[0].frames[(int)icons[0].frame]);
				icons[0].sprite.setPosition(float(j * 32), float(i * 32));
				app.draw(icons[0].sprite);
			}

			if (map[i][j] == 'U')
			{
				icons[1].sprite.setTextureRect(icons[1].frames[(int)icons[1].frame]);
				icons[1].sprite.setPosition(float(j * 32), float(i * 32));
				app.draw(icons[1].sprite);
			}

			if (map[i][j] == 'C')
			{
				icons[2].sprite.setTextureRect(icons[2].frames[(int)icons[2].frame]);
				icons[2].sprite.setPosition(float(j * 32), float(i * 32));
				app.draw(icons[2].sprite);
			}

			if (map[i][j] == 'A')
			{
				icons[3].sprite.setTextureRect(icons[3].frames[(int)icons[3].frame]);
				icons[3].sprite.setPosition(float(j * 32), float(i * 32));
				app.draw(icons[3].sprite);
			}
		}
}